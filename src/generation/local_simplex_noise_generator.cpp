#include "generation/local_simplex_noise_generator.h"

#include "helpers/math.h"

#include <ctime>
#include <algorithm>

namespace feudosim 
{

LocalSimplexNoiseGenerator::LocalSimplexNoiseGenerator() :
  random_engine_((unsigned int)time(0)),
  orientation_count_(16),
  permutation_count_(256)
{
  FillOrientationTables();
  FillPermutationTables();
}

LocalSimplexNoiseGenerator::~LocalSimplexNoiseGenerator() 
{

}

void LocalSimplexNoiseGenerator::Seed()
{
  std::shuffle(permutations_.begin(), permutations_.end(), random_engine_);
}

double LocalSimplexNoiseGenerator::Generate(double x, double y)
{
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

  // Get the grid coordinates of the first simplex point by skewing the coordinates of the current point and rounding down 
  double skew_value = (x + y) * general_skew;
  Vector2<size_t> skewed_first, skewed_second, skewed_third;
  skewed_first.x = (int)(x + skew_value);
  skewed_first.y = (int)(y + skew_value);

  // Unskew the first simplex point to get its simplex space coordinates
  double unskew_value = (skewed_first.x + skewed_first.y) * general_unskew;
  Vector2<double> unskewed_first;
  unskewed_first.x = (double)skewed_first.x - unskew_value;
  unskewed_first.y = (double)skewed_first.y - unskew_value;

  Vector2<double> dist_first, dist_second, dist_third;
  // Calculate distance between current point and the first corner
  dist_first.x =  x - unskewed_first.x;
  dist_first.y =  y - unskewed_first.y;

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

  return 70.0 * (noise_first + noise_second + noise_third);
}

void LocalSimplexNoiseGenerator::FillOrientationTables()
{
  orientations_.resize(orientation_count_);
  for (size_t or_it = 0; or_it < orientation_count_; ++or_it)
  {
    orientations_[or_it].x = cos(2 * math::PI / orientation_count_ * or_it);
    orientations_[or_it].y = sin(2 * math::PI / orientation_count_ * or_it);
  }
}

void LocalSimplexNoiseGenerator::FillPermutationTables()
{
  permutations_.resize(permutation_count_);
  for (size_t i = 0; i < permutation_count_; ++i)
    permutations_[i] = i;
}

size_t LocalSimplexNoiseGenerator::GetOrientationPosFromTable(const Vector2<size_t> &position)
{
  return permutations_[(position.x + permutations_[position.y % (permutation_count_ - 1)]) % (permutation_count_ - 1)] % (orientation_count_ - 1);
}

}  // namespace feudosim