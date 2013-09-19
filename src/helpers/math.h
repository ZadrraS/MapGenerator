#ifndef FEUDOSIM_HELPERS_MATH_H_
#define FEUDOSIM_HELPERS_MATH_H_

namespace feudosim {

namespace math
{

const double PI = 3.141592653589793;

float InterpolateLinear(double x0, double x1, double alpha)
{
   return x0 * (1 - alpha) + alpha * x1;
}

double InterpolateCosine(double y1, double y2, double mu)
{
   double mu2 = (1-cos(mu*PI))/2;
   return(y1*(1-mu2)+y2*mu2);
}

double InterpolateCubic(double y0, double y1, double y2, double y3, double mu)
{
   double a0,a1,a2,a3,mu2;

   mu2 = mu*mu;
   a0 = y3 - y2 - y0 + y1;
   a1 = y0 - y1 - a0;
   a2 = y2 - y0;
   a3 = y1;

   return a0*mu*mu2+a1*mu2+a2*mu+a3;
}

}  // namespace math
}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_MATH_H_