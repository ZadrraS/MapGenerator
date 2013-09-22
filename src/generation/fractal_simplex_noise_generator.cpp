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

  double noise_left, noise_top, noise_right;
  double tempdis;
  double skew_value, unskew_value;
  double general_skew = (sqrt(3.0) - 1.0) * 0.5;
  double general_unskew = (3.0 - sqrt(3.0)) / 6.0;

  Vector2<double> dist_left, dist_top, dist_right;
  Vector2<size_t> orient_left, orient_top, orient_right;

  double amplitude = 1.0;
  double total_amplitude = 0.0;
  for (size_t octave = 0; octave < octave_count_; ++octave)
  {
    amplitude *= gain_;
    total_amplitude += amplitude;
  }
  
  double frequency = 1.0;
  for (size_t y = 0; y < noise_map.GetHeight(); ++y)
  {
    for (size_t x = 0; x < noise_map.GetWidth(); ++x)
    {
      amplitude = 1.0;
      frequency = 1.0 / (double)(noise_map.GetWidth() * period_);

      for (size_t octave = 0; octave < octave_count_; ++octave)
      {
        double grid_x = (double)x * frequency;
        double grid_y = (double)y * frequency;
        double mid_point = noise_map.GetHeight() * 0.5 * frequency;
        skew_value = (grid_x + grid_y) * general_skew;
        orient_left.x = (int)(grid_x + skew_value);
        orient_left.y = (int)(grid_y + skew_value);

        unskew_value = (orient_left.x + orient_left.y) * general_unskew;
        dist_left.x = grid_x - (double)orient_left.x + unskew_value;
        dist_left.y = grid_y - (double)orient_left.y + unskew_value;

        if (dist_left.x > dist_left.y)
        {
          orient_top.x = 1 + orient_left.x;
          orient_top.y = orient_left.y;
        }
        else
        {
          orient_top.x = orient_left.x;
          orient_top.y = 1 + orient_left.y;
        }

        orient_right.x = 1 + orient_left.x;
        orient_right.y = 1 + orient_left.y;

        dist_top.x = dist_left.x - (orient_top.x - orient_left.x) + general_unskew;
        dist_top.y = dist_left.y - (orient_top.y - orient_left.y) + general_unskew;

        dist_right.x = dist_left.x - 1.0 + general_unskew + general_unskew;
        dist_right.y = dist_left.y - 1.0 + general_unskew + general_unskew;

        tempdis = 0.5 - dist_left.x * dist_left.x - dist_left.y * dist_left.y;
        if (tempdis < 0.0)
          noise_left = 0.0;
        else
          noise_left = tempdis * tempdis * tempdis * tempdis * dist_left.DotProduct(orientations_[GetOrientationPosFromTable(orient_left)]);

        tempdis = 0.5 - dist_top.x * dist_top.x - dist_top.y * dist_top.y;
        if (tempdis < 0.0)
          noise_top = 0.0;
        else
          noise_top = tempdis * tempdis * tempdis * tempdis * dist_top.DotProduct(orientations_[GetOrientationPosFromTable(orient_top)]);

        tempdis = 0.5 - dist_right.x * dist_right.x - dist_right.y * dist_right.y;
        if (tempdis < 0.0)
          noise_right = 0.0;
        else
          noise_right = tempdis * tempdis * tempdis * tempdis * dist_right.DotProduct(orientations_[GetOrientationPosFromTable(orient_right)]);

        noise_map.At(x, y) += (noise_left + noise_top + noise_right) * amplitude;

        amplitude *= gain_;
        frequency *= lacunarity_;
      }
    }
  }

  noise_map.Normalize();

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