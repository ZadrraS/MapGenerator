#include "generation/fractal_simplex_noise_generator.h"

#include "helpers/math.h"

#include <boost/foreach.hpp>
#include <algorithm>

namespace feudosim 
{

FractalSimplexNoiseGenerator::FractalSimplexNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity) :
  FractalNoiseGenerator(octave_count, period, gain, lacunarity),
  random_engine_((unsigned int)time(0)),
  orientation_count_(256),
  permutation_count_(256)
{
  FillOrientationTables();
  FillPermutationTables();
}

FractalSimplexNoiseGenerator::~FractalSimplexNoiseGenerator() 
{

}

Array2D<float> FractalSimplexNoiseGenerator::Generate(size_t width, size_t height)
{
  Array2D<float> noise_map(width, height);
  noise_map.SetTo(0.0f);

  std::shuffle(permutations_.begin(), permutations_.end(), random_engine_);

  double general_skew = (sqrt(3.0) - 1.0) * 0.5;
  double general_unskew = (3.0 - sqrt(3.0)) / 6.0;

  /* Naming for the corners of the simplex:
       third
       /    \
      /      \
   first -- second

   or
   
   second -- third
      \      /
       \    /
        first

    so that after skewing we'd get:
    second -- third
      |      / |
      |    /   |
      |  /     |
    first -- second
  */

  double amplitude = 1.0;
  double total_amplitude = 0.0;
  for (size_t octave = 0; octave < octave_count_; ++octave)
  {
    amplitude *= gain_;
    total_amplitude += amplitude;
  }
  
  double frequency = 1.0;
  for (size_t y = 0; y < noise_map.height(); ++y)
  {
    for (size_t x = 0; x < noise_map.width(); ++x)
    {
      amplitude = 1.0;
      frequency = 1.0 / (double)(noise_map.width() * period_);

      for (size_t octave = 0; octave < octave_count_; ++octave)
      {
        double simplex_x = (double)x * frequency;
        double simplex_y = (double)y * frequency;
       
        // Get the grid coordinates of the first simplex point by skewing the coordinates of the current point and rounding down 
        double skew_value = (simplex_x + simplex_y) * general_skew;
        Vector2<size_t> skewed_first, skewed_second, skewed_third;
        skewed_first.x = (int)(simplex_x + skew_value);
        skewed_first.y = (int)(simplex_y + skew_value);

        // Unskew the first simplex point to get its simplex space coordinates
        double unskew_value = (skewed_first.x + skewed_first.y) * general_unskew;
        Vector2<double> unskewed_first;
        unskewed_first.x = (double)skewed_first.x - unskew_value;
        unskewed_first.y = (double)skewed_first.y - unskew_value;

        Vector2<double> dist_first, dist_second, dist_third;
        // Calculate distance between current point and the first corner
        dist_first.x =  simplex_x - unskewed_first.x;
        dist_first.y =  simplex_y - unskewed_first.y;

        // Find which triangle on the skewed grid the current point occupies. 
        // Since we know the distance to the lower left point, the check is simple:
        // if dist.x > dist.y, its lower right
        // if dist.y > dist.x, its upper left
        if (dist_first.x > dist_first.y)
        {
          skewed_second.x = skewed_first.x + 1;
          skewed_second.y = skewed_first.y;

          dist_second.x = dist_first.x - 1.0 + general_unskew;
          dist_second.y = dist_first.y + general_unskew;
        }
        else
        {
          skewed_second.x = skewed_first.x;
          skewed_second.y = skewed_first.y + 1;

          dist_second.x = dist_first.x + general_unskew;
          dist_second.y = dist_first.y - 1.0 + general_unskew;
        }

        skewed_third.x = skewed_first.x + 1;
        skewed_third.y = skewed_first.y + 1;

        // Since we're moving by x and y axes unskewing value is (1.0 + 1.0) * general_unskew
        dist_third.x = dist_first.x - 1.0 + 2.0 * general_unskew;
        dist_third.y = dist_first.y - 1.0 + 2.0 * general_unskew;

        double dist = std::max(0.0, 0.5 - dist_first.x * dist_first.x - dist_first.y * dist_first.y);
        double noise_first = dist * dist * dist * dist * dist_first.DotProduct(orientations_[GetOrientationPosFromTable(skewed_first)]);

        dist = std::max(0.0, 0.5 - dist_second.x * dist_second.x - dist_second.y * dist_second.y);
        double noise_second = dist * dist * dist * dist * dist_second.DotProduct(orientations_[GetOrientationPosFromTable(skewed_second)]);

        dist = std::max(0.0, 0.5 - dist_third.x * dist_third.x - dist_third.y * dist_third.y);
        double noise_third = dist * dist * dist * dist * dist_third.DotProduct(orientations_[GetOrientationPosFromTable(skewed_third)]);

        noise_map.At(x, noise_map.height() - y - 1) += 70.0 * (noise_first + noise_second + noise_third) * amplitude;

        amplitude *= gain_;
        frequency *= lacunarity_;
      }
    }
  }

  noise_map /= total_amplitude;

  return noise_map;
}

void FractalSimplexNoiseGenerator::FillOrientationTables()
{
  orientations_.resize(orientation_count_);
  for (size_t or_it = 0; or_it < orientation_count_; ++or_it)
  {
    orientations_[or_it].x = cos(2 * math::PI / orientation_count_ * or_it);
    orientations_[or_it].y = sin(2 * math::PI / orientation_count_ * or_it);
  }
}

void FractalSimplexNoiseGenerator::FillPermutationTables()
{
  permutations_.resize(permutation_count_);
  for (size_t i = 0; i < permutation_count_; ++i)
    permutations_[i] = i;
}

size_t FractalSimplexNoiseGenerator::GetOrientationPosFromTable(const Vector2<size_t> &position)
{
  return permutations_[(position.x + permutations_[position.y % (permutation_count_ - 1)]) % (permutation_count_ - 1)] % (orientation_count_ - 1);
}

}  // namespace feudosim