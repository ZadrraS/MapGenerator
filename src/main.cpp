#include "generation/fractal_simplex_noise_generator.h"
#include "generation/fractal_value_noise_generator.h"
#include "generation/poisson_point_sampler.h"
#include "helpers/sfml_conversion.h"
#include "map/array2d.h"
#include "helpers/vector_2.h"


#include <SFML/Graphics.hpp>

#include <iostream>

void PasteArray2DToSprite(const feudosim::Array2D<float> &array2d, sf::Texture &texture, sf::Sprite &sprite)
{
   uint8_t *array2d_data = feudosim::ConvertArrayToSFMLFormat(array2d);
   texture.update((const sf::Uint8 *)array2d_data);
   sprite.setTexture(texture);

   delete [] array2d_data;
}

int main(int argc, char const *argv[])
{
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Test");

 // feudosim::FractalSimplexNoiseGenerator noise_generator(16, 1.0, 0.65, 2.0);
 // feudosim::Array2D<float> noise_image = noise_generator.Generate(1024, 1024);

 // sf::Texture texture;
 // texture.create(1024, 1024);
  //sf::Sprite sprite;
 // PasteArray2DToSprite(noise_image, texture, sprite);
  std::vector< feudosim::Vector2<int> > points;
  feudosim::PoissonPointSampler point_sampler;
  point_sampler.Sample(feudosim::Rectangle(0, 0, 1024, 1024), 10, 50, 200, points);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        points.clear();
        point_sampler.Sample(feudosim::Rectangle(0, 0, 1024, 1024), 5, 50, 200, points);
       // noise_image = noise_generator.Generate(1024, 1024);
       // PasteArray2DToSprite(noise_image, texture, sprite);
      }
    }

    window.clear();
    //window.draw(sprite);
    feudosim::DrawPoints(window, points);
    window.display();
  }

 // delete [] noise_image_data;

  return 0;
}