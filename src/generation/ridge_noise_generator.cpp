#include "generation/ridge_noise_generator.h"

#include "helpers/math.h"

#include <boost/foreach.hpp>
#include <algorithm>
#include <iostream>
namespace feudosim 
{

RidgeNoiseGenerator::RidgeNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity, double offset) :
  FractalNoiseGenerator(octave_count, period, gain, lacunarity),
  offset_(offset)
{

}

RidgeNoiseGenerator::~RidgeNoiseGenerator() 
{

}

Array2D<float> RidgeNoiseGenerator::Generate(size_t width, size_t height)
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
        double value = local_noise_generator_.Generate((double)x * frequency, (double)y * frequency);
        if (value < 0.0)
          value = -value;
        
        value = offset_ - value;
        value *= value;
        noise_map.At(x, y) += value * amplitude;

        amplitude *= gain_;
        frequency *= lacunarity_;
      }
    }
  }

  noise_map.Normalize(-0.8f, 1.0f);
  
  return noise_map;
}

}  // namespace feudosim