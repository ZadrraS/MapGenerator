#include "generation/fractal_simplex_noise_generator.h"

#include "helpers/math.h"

#include <boost/foreach.hpp>
#include <algorithm>

namespace feudosim 
{

FractalSimplexNoiseGenerator::FractalSimplexNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity) :
  FractalNoiseGenerator(octave_count, period, gain, lacunarity)
{

}

FractalSimplexNoiseGenerator::~FractalSimplexNoiseGenerator() 
{

}

Array2D<float> FractalSimplexNoiseGenerator::Generate(size_t width, size_t height)
{
  Array2D<float> noise_map(width, height);
  noise_map.SetTo(0.0f);

  local_noise_generator_.Seed();

  double amplitude = 1.0;
  double total_amplitude = 0.0;
  for (size_t octave = 0; octave < octave_count_; ++octave)
  {
    amplitude *= gain_;
    total_amplitude += amplitude;
  }
  
  double frequency = 1.0;
  for (size_t y = 0; y < noise_map.height(); ++y)
  {
    for (size_t x = 0; x < noise_map.width(); ++x)
    {
      amplitude = 1.0;
      frequency = 1.0 / (double)(noise_map.width() * period_);

      for (size_t octave = 0; octave < octave_count_; ++octave)
      {
        noise_map.At(x, y) += local_noise_generator_.Generate((double)x * frequency, (double)y * frequency) * amplitude;

        amplitude *= gain_;
        frequency *= lacunarity_;
      }
    }
  }

  noise_map /= total_amplitude;

  return noise_map;
}


}  // namespace feudosim