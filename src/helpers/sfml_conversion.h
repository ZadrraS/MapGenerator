#ifndef FEUDOSIM_SFML_CONVERSION_H_
#define FEUDOSIM_SFML_CONVERSION_H_

#include "map/array2d.h"

namespace feudosim {

uint8_t *ConvertArrayToSFMLFormat(const Array2D<float> &array2d);

}  // namespace feudosim

#endif  // FEUDOSIM_SFML_CONVERSION_H_