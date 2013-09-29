#include "generation/fractal_simplex_noise_generator.h"
#include "generation/fractal_value_noise_generator.h"
#include "generation/ridge_noise_generator.h"
#include "generation/poisson_point_sampler.h"
#include "graphics/sfml_conversion.h"
#include "graphics/map_render_gradient.h"
#include "helpers/array2d.h"
#include "helpers/vector2.h"
#include "helpers/segment2.h"
#include "helpers/gradient.h"
#include "helpers/math.h"

#include <SFML/Graphics.hpp>
#include <boost/polygon/voronoi.hpp>
#include <boost/polygon/polygon.hpp>

#include <iostream>

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;

namespace boost 
{
namespace polygon 
{

template <>
struct geometry_concept< feudosim::Vector2<int> > { typedef point_concept type; };
   
template <>
struct point_traits< feudosim::Vector2<int> > {
  typedef int coordinate_type;
    
  static inline coordinate_type get(const feudosim::Vector2<int> &point, orientation_2d orient) {
    return (orient == HORIZONTAL) ? point.x : point.y;
  }
};

template <>
struct geometry_concept< feudosim::Segment2<int> > { typedef segment_concept type; };

template <>
struct point_traits< feudosim::Segment2<int> > {
  typedef int coordinate_type;
  typedef feudosim::Vector2<int> point_type;
    
  static inline point_type get(const feudosim::Segment2<int> &segment, direction_1d dir) {
    return dir.to_int() ? segment.point1 : segment.point0;
  }
};




}  // polygon
}  // boost
typedef boost::polygon::voronoi_diagram<double>::cell_type cell_type;
typedef boost::polygon::voronoi_diagram<double>::edge_type edge_type;
typedef boost::polygon::voronoi_diagram<double>::vertex_type vertex_type;

void DrawVoronoi(sf::RenderWindow &window, boost::polygon::voronoi_diagram<double> &vd, std::vector< feudosim::Vector2<int> > &points)
{
  for (boost::polygon::voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
        it != vd.cells().end(); ++it)
   {
      const cell_type& cell = *it;
      const edge_type* edge = cell.incident_edge();

      do
      {
         if (edge->is_primary())
         {
            // Easy finite edge case
            if (edge->is_finite())
            {
               // Without this check each edge would be drawn twice
               // as they are really half-edges
               if (edge->cell()->source_index() < 
                   edge->twin()->cell()->source_index())
               {
                  sf::Vertex line[] =
                  {
                      sf::Vertex(sf::Vector2f(edge->vertex0()->x(), edge->vertex0()->y()), sf::Color::Black),
                      sf::Vertex(sf::Vector2f(edge->vertex1()->x(), edge->vertex1()->y()), sf::Color::Black)
                  };

                  window.draw(line, 2, sf::Lines);
               }
            }
            else
            {
               // This covers the infinite edge case in question.
               const vertex_type* v0 = edge->vertex0();
               // Again, only consider half the half-edges, ignore edge->vertex1()
               // to avoid overdrawing the lines
               if (v0)
               {
                  // Direction of infinite edge if perpendicular to direction
                  // between the points owning the two half edges. 
                  // Take the rotated right vector and multiply by a large 
                  // enough number to reach your bounding box
                  feudosim::Vector2<int> p1 = points[edge->cell()->source_index()];
                  feudosim::Vector2<int> p2 = points[edge->twin()->cell()->source_index()];
                  int end_x = (p1.y - p2.y) * 1024;
                  int end_y = (p1.x - p2.x) * -1024;

                  sf::Vertex line[] =
                  {
                      sf::Vertex(sf::Vector2f(v0->x(), v0->y()), sf::Color::Black),
                      sf::Vertex(sf::Vector2f(end_x, end_y), sf::Color::Black)
                  };
                  window.draw(line, 2, sf::Lines);
                  //draw_line(v0->x(), v0->y(),
                         //   end_x, end_y);
               }
            }
         }
         edge = edge->next();
      } while (edge != cell.incident_edge());
   }
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Test");

  feudosim::FractalSimplexNoiseGenerator noise_generator(16, 0.5, 0.65, 2.0);
  feudosim::Array2D<float> noise_image;
  feudosim::MapRenderGradient render_gradient;
  render_gradient.AddPoint(-1.0000, sf::Color(0, 0, 128, 255)); // deeps
  render_gradient.AddPoint(-0.2500, sf::Color(0, 0, 255, 255)); // shallow
  render_gradient.AddPoint(0.0000, sf::Color(0, 128, 255, 255)); // shore
  render_gradient.AddPoint(0.0625, sf::Color(240, 240, 64, 255)); // sand
  render_gradient.AddPoint(0.1250, sf::Color(32, 160, 0, 255)); // grass
  render_gradient.AddPoint(0.5500, sf::Color(192, 224, 64, 255)); // dirt
  render_gradient.AddPoint(0.7500, sf::Color(128, 128, 128, 255)); // rock
  render_gradient.AddPoint(1.0000, sf::Color(255, 255, 255, 255)); // snow

  feudosim::MapRenderGradient render_heightmap;
  render_heightmap.AddPoint(-1.0, sf::Color(0, 0, 0 , 255));
  render_heightmap.AddPoint(1.0, sf::Color(255, 255, 255, 255));

  feudosim::MapRenderGradient render_tempmap;
  render_tempmap.AddPoint(0.0, sf::Color(0, 0, 255 , 255));
  render_tempmap.AddPoint(1.0, sf::Color(255, 0, 0, 255));

  feudosim::RidgeNoiseGenerator ridge_generator(3, 0.5, 0.25, 2.0, 1.0);
  feudosim::Array2D<float> ridge_noise;
//  ridge_noise.Abs();
  //ridge_noise = feudosim::Array2D<float>(1024, 1024, 1.0f) - ridge_noise;
  //ridge_noise.Abs();
 // sf::Texture texture;
 // texture.create(1024, 1024);
  //sf::Sprite sprite;
 // PasteArray2DToSprite(noise_image, texture, sprite);
 
  std::vector< feudosim::Vector2<int> > points;
  feudosim::PoissonPointSampler point_sampler;
  point_sampler.Sample(feudosim::Rectangle(0, 0, 1024, 1024), 10, 50, 300, points);

  boost::polygon::voronoi_diagram<double> vd;
  boost::polygon::construct_voronoi(points.begin(), points.end(), &vd);

 feudosim::Array2D<float> final_noise;

 feudosim::Array2D<float> circular_mask(1024, 1024, 0.0f);
 for (size_t y = 0; y < circular_mask.height(); ++y)
 {
    for (size_t x = 0; x < circular_mask.width(); ++x)
    {
      double dist_value =  sqrt((512.0 - x) * (512.0 - x) + (512.0 - y) * (512.0 - y));
      circular_mask.At(y, x) = -(dist_value*dist_value);
    }
 }

 circular_mask.Normalize(-0.1f, 1.0f);
 circular_mask.Clip(0.0f, 1.0f);

 feudosim::Gradient temperature_gradient;
 temperature_gradient.AddPoint(0.0, 0.0);
 temperature_gradient.AddPoint(0.1, 0.4);
 temperature_gradient.AddPoint(0.5, 1.0);
 temperature_gradient.AddPoint(0.9, 0.4);
 temperature_gradient.AddPoint(1.0, 0.0);

 feudosim::Array2D<float> temperature_map(1024, 1024);
 temperature_gradient.Paste(temperature_map, feudosim::math::InterpolateLinear);

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
        point_sampler.Sample(feudosim::Rectangle(0, 0, 1024, 1024), 10, 50, 300, points);
        vd.clear();
        boost::polygon::construct_voronoi(points.begin(), points.end(), &vd);
        noise_image = noise_generator.Generate(1024, 1024);
       // noise_image.Normalize();
        temperature_gradient.Paste(temperature_map, feudosim::math::InterpolateLinear);
        temperature_map = temperature_map + (noise_image * 0.2);
        temperature_map.Clip(0.0, 1.0);
       // temperature_map.Normalize();
        //noise_image.Normalize(-1.0f, 1.0f);
       /*ridge_noise = ridge_generator.Generate(1024, 1024);
        ridge_noise.Normalize(-0.0f, 0.5f);

        noise_image.Normalize(-1.0f, 1.0f);
        final_noise = ((noise_image + ridge_noise) + 1.0) * circular_mask - 1.0; 
        final_noise.Normalize(-1.0f, 1.0f);*/
       // final_noise.Clip(-1.0, 1.0);
      //  final_noise.Normalize();
       // PasteArray2DToSprite(noise_image, texture, sprite);
      }
    }

    window.clear();
  //\  render_gradient.Draw(window, noise_image);
    //render_gradient.Draw(window, final_noise);
    render_tempmap.Draw(window, temperature_map);
    //window.draw(sprite);
   // feudosim::DrawPoints(window, points);
   // DrawVoronoi(window, vd, points);
    window.display();
  }

 // delete [] noise_image_data;

  return 0;
}