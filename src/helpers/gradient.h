#ifndef FEUDOSIM_HELPERS_GRADIENT_H_
#define FEUDOSIM_HELPERS_GRADIENT_H_

#include "helpers/array2d.h"

#include <vector>

namespace feudosim 
{

class Gradient 
{
 public:
  Gradient();
  ~Gradient();

  void AddPoint(double point, double value);
  void Clear();

  void Paste(Array2D<float> &array2d, double (&interp)(double, double, double), bool vertical = true);

 private:
  typedef std::pair<double, double> GradientPoint;
  static bool GradientAscendingComparator(const GradientPoint &point1, const GradientPoint &point2)
  {
    return point1.first < point2.first;
  }

  std::vector< std::pair<double, double> > gradient_;
  
};

}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_GRADIENT_H_