#ifndef FEUDOSIM_HELPERS_SEGMENT2_H_
#define FEUDOSIM_HELPERS_SEGMENT2_H_

#include "helpers/vector2.h"

namespace feudosim 
{

template <class T>
class Segment2 
{
 public:
  Segment2() :
    point0((T)0, (T)0),
    point1((T)0, (T)0)
  {

  }

  Segment2(const Vector2<T> &point0, const Vector2<T> &point1)
  {
    this->point0 = point0;
    this->point1 = point1;
  }

  ~Segment2()
  {

  }

  Vector2<T> point0;
  Vector2<T> point1;
  
};

}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_SEGMENT2_H_