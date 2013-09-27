#include "graphics/sfml_conversion.h"

#include <boost/foreach.hpp>

namespace feudosim 
{

uint8_t *ConvertArrayToSFMLFormat(const Array2D<float> &array2d) 
{
  uint8_t *sfml_data = new uint8_t[array2d.width() * array2d.height() * 4];
  for (size_t y = 0; y < array2d.height(); ++y) {
    for (size_t x = 0; x < array2d.width(); ++x) {
      for (size_t i = 0; i < 3; i++)
        sfml_data[(y * array2d.width() + x) * 4 + i] = (uint8_t)(array2d.At(x, y) * 255);

      sfml_data[(y * array2d.width() + x) * 4 + 3] = 255;      
    }
  }

  return sfml_data;
}

void DrawPoints(sf::RenderWindow &render_window, const std::vector< Vector2<int> > &points)
{
  BOOST_FOREACH(const Vector2<int> &point, points)
  {
    sf::CircleShape dot(3.0f);
    dot.setFillColor(sf::Color::Black);
    dot.setPosition(point.x, point.y);
    render_window.draw(dot);
  }
}

void PasteArray2DToSprite(const Array2D<float> &array2d, sf::Texture &texture, sf::Sprite &sprite)
{
   uint8_t *array2d_data = feudosim::ConvertArrayToSFMLFormat(array2d);
   texture.update((const sf::Uint8 *)array2d_data);
   sprite.setTexture(texture);

   delete [] array2d_data;
}

}  // namespace feudosim