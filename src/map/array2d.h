#ifndef FEUDOSIM_MAP_ARRAY2D_H_
#define FEUDOSIM_MAP_ARRAY2D_H_

#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <cmath>

namespace feudosim 
{

template <typename T>
class Array2D 
{
 public:
  Array2D() 
  {
    data_ = NULL;
    width_ = 0;
    height_ = 0;
  }

  Array2D(size_t width, size_t height) 
  {
    data_ = NULL;
    Create(width, height);
  }

  Array2D(size_t width, size_t height, const T &value) 
  {
    data_ = NULL;
    Create(width, height);
    SetTo(value);
  }

  Array2D(const Array2D &array2d) 
  {
    data_ = NULL;
    CopyFrom(array2d);
  }

  ~Array2D() 
  {
    Clean();
  }

  Array2D &operator*=(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) *= array2d.At(x, y);
      }
    }

    return *this;
  }

  Array2D operator*(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) *= array2d.At(x, y);
      }
    }
    
    return new_array;
  }

  Array2D &operator/=(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) /= array2d.At(x, y);
      }
    }

    return *this;
  }

  Array2D operator/(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) /= array2d.At(x, y);
      }
    }
    
    return new_array;
  }

  Array2D &operator+=(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) += array2d.At(x, y);
      }
    }

    return *this;
  }

  Array2D operator+(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) += array2d.At(x, y);
      }
    }
    
    return new_array;
  }

  Array2D &operator-=(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) -= array2d.At(x, y);
      }
    }

    return *this;
  }

  Array2D operator-(const Array2D &array2d) 
  {
    if (width_ != array2d.width() || height_ != array2d.height())
      throw std::invalid_argument("Given Array2D dimensions don't match.");

    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) -= array2d.At(x, y);
      }
    }
    
    return new_array;
  }

  Array2D &operator*=(T rhs) 
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) *= rhs;
      }
    }

    return *this;
  }

  Array2D operator*(T rhs)
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) *= rhs;
      }
    }
    
    return new_array;
  }

  Array2D &operator/=(T rhs) 
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) /= rhs;
      }
    }

    return *this;
  }

  Array2D operator/(T rhs)
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) /= rhs;
      }
    }
    
    return new_array;
  }

  Array2D &operator+=(T rhs) 
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) += rhs;
      }
    }

    return *this;
  }

  Array2D operator+(T rhs)
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) += rhs;
      }
    }
    
    return new_array;
  }

  Array2D &operator-=(T rhs) 
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        At(x, y) -= rhs;
      }
    }

    return *this;
  }

  Array2D operator-(T rhs)
  {
    if (width_ == 0 || height_ == 0)
      throw std::invalid_argument("Given Array2D is empty.");

    Array2D<T> new_array(*this);
    for (size_t y = 0; y < height_; ++y)
    {
      for (size_t x = 0; x < width_; ++x)
      {
        new_array.At(x, y) -= rhs;
      }
    }
    
    return new_array;
  }

  Array2D &operator=(const Array2D &array2d) 
  {
    data_ = NULL;
    CopyFrom(array2d);

    return *this;
  }

  size_t width() const 
  {
    return width_;
  }

  size_t height() const 
  {
    return height_;
  }

  T &At(size_t x, size_t y) 
  {
    if (x > width_ || y > height_)
      throw std::invalid_argument("Given Array2D dimensions invalid.");

    return data_[y * width_ + x];
  }

  const T &At(size_t x, size_t y) const 
  {
    if (x > width_ || y > height_)
      throw std::invalid_argument("Given Array2D dimensions invalid.");

    return data_[y * width_ + x];
  }

  void Create(size_t width, size_t height) 
  {
    if (width == 0 || height == 0)
      throw std::invalid_argument("Given Array2D dimensions invalid.");

    if (width == width_ && height == height_)
      return;

    if (data_ != NULL)
      delete [] data_;

    width_ = width;
    height_ = height;
    data_ = new T[width_ * height_];
  }

  void CopyFrom(const Array2D &array2d) 
  {
    if (array2d.width() == 0 || array2d.height() == 0)
      throw std::invalid_argument("Given Array2D dimensions invalid.");

    Clean();
    Create(array2d.width(), array2d.height());

    memcpy((void *)data_, (const void *)array2d.data_, width_ * height_ * sizeof(T));
  }

  void SetTo(const T &value) 
  {
    if (data_ != NULL)
      memset((void *)data_, (int)value, width_ * height_ * sizeof(T));
  }

  void Clean() 
  {
    if (data_ != NULL)
      delete [] data_;

    width_ = 0;
    height_ = 0;
  }

  void Normalize()
  {
      Normalize((T)0.0, (T)1.0);
  }


  void Normalize(const T &min_value, const T &max_value)
  {
    if (data_ != NULL)
    {
      T min_array_val = At(0, 0);
      T max_array_val = At(0, 0);
      for (size_t y = 0; y < height_; ++y)
      {
        for (size_t x = 0; x < width_; ++x)
        {
          if (At(x, y) > max_array_val)
            max_array_val = At(x, y);
          if (At(x, y) < min_array_val)
            min_array_val = At(x, y);
        }
      }

      for (size_t y = 0; y < height_; ++y)
      {
        for (size_t x = 0; x < width_; ++x)
        {
          At(x, y) = (At(x, y) - min_array_val) / (max_array_val - min_array_val);
          At(x, y) = At(x, y) * (max_value - min_value) + min_value;
        }
      }
    }
  }

  void Abs()
  { 
    if (data_ != NULL)
    {
      for (size_t y = 0; y < height_; ++y)
      {
        for (size_t x = 0; x < width_; ++x)
        {
          At(x, y) = (T)fabs(At(x, y));
        }
      }
    }
  }

  void Clip(const T &min_value, const T &max_value)
  {
    if (data_ != NULL)
    {
      for (size_t y = 0; y < height_; ++y)
      {
        for (size_t x = 0; x < width_; ++x)
        {
          if (At(x, y) < min_value)
            At(x, y) = min_value;
          else if (At(x, y) > max_value)
            At(x, y) = max_value;
        }
      }
    }
  }

 private:  
  size_t width_, height_;
  T *data_;

};

}  // namespace feudosim

#endif  // FEUDOSIM_MAP_ARRAY2D_H_