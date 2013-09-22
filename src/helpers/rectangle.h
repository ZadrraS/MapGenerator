#ifndef FEUDOSIM_HELPERS_RECTAMGLE_H_
#define FEUDOSIM_HELPERS_RECTAMGLE_H_

namespace feudosim 
{

class Rectangle 
{
 public:
  Rectangle(int x, int y, int width, int height)
  {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  ~Rectangle()
  {

  }

  int x, y;
  int width, height;
};

}  // namespace feudosim

#endif  // FEUDOSIM_HELPERS_RECTAMGLE_H_