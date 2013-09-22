#ifndef FEUDOSIM_HELPERS_MATH_H_
#define FEUDOSIM_HELPERS_MATH_H_

#include <cmath>

namespace feudosim 
{
namespace math
{

const double PI = 3.141592653589793;

inline float InterpolateLinear(double x0, double x1, double alpha)
{
   return x0 * (1.0 - alpha) + alpha * x1;
}

inline double InterpolateCosine(double x0, double x1, double alpha)
{
   double cos_alpha = (1.0 - cos(alpha * PI)) / 2.0;
   return InterpolateLinear(x0, x1, cos_alpha);
}

inline double InterpolateCubic(double x0, double x1, double x2, double x3, double alpha)
{
   double alpha_sq = alpha * alpha;
   double a0 = x3 - x2 - x0 + x1;
   double a1 = x0 - x1 - a0;
   double a2 = x2 - x0;
   double a3 = x1;

   return a0 * alpha * alpha_sq + a1 * alpha_sq + a2 * alpha + a3;
}

}  // namespace math
}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_MATH_H_