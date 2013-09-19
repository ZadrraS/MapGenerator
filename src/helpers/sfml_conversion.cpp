#include "helpers/sfml_conversion.h"

namespace feudosim 
{

uint8_t *ConvertArrayToSFMLFormat(const Array2D<float> &array2d) 
{
  uint8_t *sfml_data = new uint8_t[array2d.GetWidth() * array2d.GetHeight() * 4];
  for (size_t y = 0; y < array2d.GetHeight(); ++y) {
    for (size_t x = 0; x < array2d.GetWidth(); ++x) {
      for (size_t i = 0; i < 3; i++)
        sfml_data[(y * array2d.GetWidth() + x) * 4 + i] = (uint8_t)(array2d.At(x, y) * 255);

      sfml_data[(y * array2d.GetWidth() + x) * 4 + 3] = 255;      
    }
  }

  return sfml_data;
}

}  // namespace feudosim