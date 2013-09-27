#include "graphics/map_render_gradient.h"

#include "graphics/sfml_conversion.h"

#include <stdexcept>

namespace feudosim 
{

MapRenderGradient::MapRenderGradient() 
{

}

MapRenderGradient::~MapRenderGradient() 
{

}

void MapRenderGradient::Clear()
{
  gradient_.clear();
}

void MapRenderGradient::AddPoint(double value, const sf::Color &color)
{
  gradient_.push_back(std::pair<double, sf::Color>(value, color));
}

void MapRenderGradient::Draw(sf::RenderWindow &window, const Array2D<float> &map)
{
  if (map.width() == 0 || map.height() == 0)
    return;
  
  if (gradient_.empty())
    throw std::invalid_argument("Gradient values not filled.");

  std::sort(gradient_.begin(), gradient_.end(), GradientAscendingComparator);

  sf::Uint8 *sfml_data = new sf::Uint8[map.width() * map.height() * 4];
  for (size_t y = 0; y < map.height(); ++y)
  {
    for (size_t x = 0; x < map.width(); ++x)
    {
      sf::Color draw_color = gradient_[0].second;
      for (size_t i = 0; i < gradient_.size() - 1; i++)
      {
        if (map.At(x, y) <= gradient_[i + 1].first && map.At(x, y) > gradient_[i].first)
        {
          draw_color = InterpolateColor(gradient_[i].second, gradient_[i + 1].second, (map.At(x, y) - gradient_[i].first) / (gradient_[i + 1].first - gradient_[i].first));
          break;
        }
      }

      sfml_data[(y * map.width() + x) * 4 + 0] = draw_color.r;
      sfml_data[(y * map.width() + x) * 4 + 1] = draw_color.g;
      sfml_data[(y * map.width() + x) * 4 + 2] = draw_color.b;
      sfml_data[(y * map.width() + x) * 4 + 3] = draw_color.a;
    }
  }

  sf::Texture texture;
  texture.create(window.getSize().x, window.getSize().y);
  sf::Sprite sprite;
  texture.update((const sf::Uint8 *)sfml_data);
  sprite.setTexture(texture);

  window.draw(sprite);

  delete [] sfml_data;
}

sf::Color MapRenderGradient::InterpolateColor(const sf::Color &color1, const sf::Color &color2, double alpha)
{
  return sf::Color((sf::Uint8)(color1.r * (1.0 - alpha) + color2.r * alpha),
    (sf::Uint8)(color1.g * (1.0 - alpha) + color2.g * alpha),
    (sf::Uint8)(color1.b * (1.0 - alpha) + color2.b * alpha),
    (sf::Uint8)(color1.a * (1.0 - alpha) + color2.a * alpha));
}

}  // namespace feudosim