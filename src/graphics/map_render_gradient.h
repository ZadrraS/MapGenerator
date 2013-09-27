#ifndef FEUDOSIM_GRAPHICS_MAP_RENDER_GRADIENT_H_
#define FEUDOSIM_GRAPHICS_MAP_RENDER_GRADIENT_H_

#include "map/array2d.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace feudosim 
{

class MapRenderGradient 
{
 public:
  MapRenderGradient();
  ~MapRenderGradient();

  void Clear();
  void AddPoint(double value, const sf::Color &color);
  void Draw(sf::RenderWindow &window, const Array2D<float> &map);
  
 private:  
  typedef std::pair<double, sf::Color> GradientPoint;
  static bool GradientAscendingComparator(const GradientPoint &point1, const GradientPoint &point2)
  {
    return point1.first < point2.first;
  }

  sf::Color InterpolateColor(const sf::Color &color1, const sf::Color &color2, double alpha);

  std::vector< std::pair<double, sf::Color> > gradient_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GRAPHICS_MAP_RENDER_GRADIENT_H_