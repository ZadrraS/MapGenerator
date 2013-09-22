#ifndef FEUDOSIM_SFML_CONVERSION_H_
#define FEUDOSIM_SFML_CONVERSION_H_

#include <SFML/Graphics.hpp>

#include "map/array2d.h"
#include "helpers/vector_2.h"

namespace feudosim 
{

uint8_t *ConvertArrayToSFMLFormat(const Array2D<float> &array2d);
void DrawPoints(sf::RenderWindow &render_window, const std::vector< Vector2<int> > &points);

}  // namespace feudosim

#endif  // FEUDOSIM_SFML_CONVERSION_H_