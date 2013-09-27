#ifndef FEUDOSIM_HELPERS_VECTOR2_H_
#define FEUDOSIM_HELPERS_VECTOR2_H_

namespace feudosim 
{

template <class T>
class Vector2 
{
 public:
  Vector2()
  {

  }

  Vector2(T x, T y)
  {
    this->x = x;
    this->y = y;
  }

  ~Vector2()
  {

  }

  T DotProduct(const Vector2<T> &vector2)
  {
    return x * vector2.x + y * vector2.y;
  }

  void CutToBoundaries(const T &min_x, const T &min_y, const T &max_x, const T &max_y)
  {
    if (x < min_x)
      x = min_x;
    if (x > max_x)
      x = max_x;
    if (y < min_y)
      y = min_y;
    if (y > max_y)
      y = max_y;
  }

  T x, y;  
};

}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_VECTOR2_H_