#include "generation/poisson_point_sampler.h"

#include "helpers/math.h"

#include <boost/foreach.hpp>

namespace feudosim 
{

PoissonPointSampler::PoissonPointSampler() 
{

}

PoissonPointSampler::~PoissonPointSampler() 
{

}

void PoissonPointSampler::Sample(const Rectangle &bounds, size_t radius_point_count, double min_distance, double max_distance, std::vector< Vector2<int> > &output_points)
{
  processing_points_.clear();
  output_points.clear();
  
  std::uniform_real_distribution<double> angle_dist(0.0, 2 * math::PI);
  std::uniform_real_distribution<double> distance_dist(min_distance, max_distance);

  std::uniform_int_distribution<int> x_distribution(bounds.x, bounds.x + bounds.width);
  std::uniform_int_distribution<int> y_distribution(bounds.y, bounds.y + bounds.height);

  Vector2<int> first_point(x_distribution(random_engine_), y_distribution(random_engine_));
  output_points.push_back(first_point);
  processing_points_.push_back(first_point);

  while (!processing_points_.empty())
  {
    std::uniform_int_distribution<size_t> point_distribution(0, processing_points_.size() - 1);
    size_t random_point_pos = point_distribution(random_engine_);

    Vector2<int> selected_point = processing_points_[random_point_pos];
    processing_points_.erase(processing_points_.begin() + random_point_pos);
    for (size_t gen_point_it = 0; gen_point_it < radius_point_count; ++gen_point_it)
    {
      double angle = angle_dist(random_engine_);
      double distance = distance_dist(random_engine_);
      Vector2<int> new_point(selected_point.x + distance * cos(angle), selected_point.y + distance * sin(angle));

      if (IsPointSolitary(new_point, min_distance, output_points) &&
        new_point.x >= bounds.x && new_point.y >= bounds.y && 
        new_point.x <= bounds.x + bounds.width && new_point.y <= bounds.y + bounds.height)
      {
        processing_points_.push_back(new_point);
        output_points.push_back(new_point);
      }
    }
  }
}

bool PoissonPointSampler::IsPointSolitary(const Vector2<int> &point, double min_distance, std::vector< Vector2<int> > &output_points)
{
  BOOST_FOREACH(const Vector2<int> &old_point, output_points)
  {
    if (GetDistanceSqr(point, old_point) < min_distance * min_distance)
      return false;
  }

  return true;
}

double PoissonPointSampler::GetDistanceSqr(const Vector2<int> &point1, const Vector2<int> &point2)
{
  return (double)(point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}

}  // namespace feudosim