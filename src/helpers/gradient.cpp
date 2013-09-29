#include "helpers/gradient.h"

#include "helpers/math.h"

#include <exception>

namespace feudosim 
{

Gradient::Gradient() 
{

}

Gradient::~Gradient() 
{

}

void Gradient::AddPoint(double point, double value)
{
  gradient_.push_back(std::pair<double, double>(point, value));
}

void Gradient::Clear()
{
  gradient_.clear();
}

void Gradient::Paste(Array2D<float> &array2d, double (&interp)(double, double, double), bool vertical)
{
  if (gradient_.empty())
    throw std::invalid_argument("Gradient is empty.");
  if (array2d.width() == 0 || array2d.height() == 0)
    throw std::invalid_argument("Input array is empty.");

  double max_gradient_pos = gradient_.back().first;
  if (vertical)
  {
    for (size_t y = 0; y < array2d.height(); ++y)
    {
      double draw_color = gradient_[0].second;
      for (size_t i = 0; i < gradient_.size() - 1; i++)
      {
        double position_normed = (double)y / array2d.height();
        double this_grad_pos = gradient_[i].first / max_gradient_pos;
        double next_grad_pos = gradient_[i + 1].first / max_gradient_pos;
        if (position_normed <= next_grad_pos && position_normed > this_grad_pos)
        {
          draw_color = interp(gradient_[i].second, gradient_[i + 1].second, (position_normed  - this_grad_pos) / (next_grad_pos - this_grad_pos));
          break;
        }
        
      }

      for (size_t x = 0; x < array2d.width(); ++x)
      {
        array2d.At(x, y) = draw_color;
      }
    }
  }
}

}  // namespace feudosim