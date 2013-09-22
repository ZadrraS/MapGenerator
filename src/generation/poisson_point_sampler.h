#ifndef FEUDOSIM_GENERATION_POISSON_POINT_SAMPLER_H_
#define FEUDOSIM_GENERATION_POISSON_POINT_SAMPLER_H_

#include "helpers/vector_2.h"
#include "map/array2d.h"
#include "helpers/rectangle.h"

#include <vector>
#include <random>

namespace feudosim 
{

class PoissonPointSampler 
{
 public:
  PoissonPointSampler();
  ~PoissonPointSampler();

  void Sample(const Rectangle &bounds, size_t radius_point_count, double min_distance, double max_distance, std::vector< Vector2<int> > &output_points);

 private:  
  bool IsPointSolitary(const Vector2<int> &point, double min_distance, std::vector< Vector2<int> > &output_points);
  double GetDistanceSqr(const Vector2<int> &point1, const Vector2<int> &point2);

  std::default_random_engine random_engine_; 
  std::vector< Vector2<int> > processing_points_;  
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_POISSON_POINT_SAMPLER_H_