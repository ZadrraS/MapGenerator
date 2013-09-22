#include "generation/fractal_value_noise_generator.h"

#include "map/array2d.h"
#include "helpers/math.h"

#include <random>
#include <ctime>

namespace feudosim 
{

FractalValueNoiseGenerator::FractalValueNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity) :
  FractalNoiseGenerator(octave_count, period, gain, lacunarity),
  random_engine_((unsigned int)time(0))
{

}

FractalValueNoiseGenerator::~FractalValueNoiseGenerator() 
{

}

Array2D<float> FractalValueNoiseGenerator::Generate(size_t width, size_t height) 
{
  Array2D<float> base_noise_map(width, height);
  base_noise_map.SetTo(0.0f);

  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  for (size_t y = 0; y < base_noise_map.GetHeight(); ++y) 
  {
    for (size_t x = 0; x < base_noise_map.GetWidth(); ++x) 
    {
      base_noise_map.At(x, y) = distribution(random_engine_);
    }
  }

  Array2D<float> noise_map(width, height);
  noise_map.SetTo(0.0f);

  float amplitude = 1.0f;
  float total_amplitude = 0.0f;
 
  for (int octave = (int)octave_count_ - 1; octave >= 0; --octave)
  {
    size_t sample_period = 1 << octave; // calculates 2 ^ k
    float sample_frequency = 1.0f / sample_period;

    amplitude *= (float)gain_;
    total_amplitude += amplitude;
    for (size_t y = 0; y < noise_map.GetHeight(); y++)
    {
      size_t sample_y0 = (y / sample_period) * sample_period;
      size_t sample_y1 = (sample_y0 + sample_period) % noise_map.GetHeight();
      float vertical_blend = (y - sample_y0) * sample_frequency;

      for (size_t x = 0; x < noise_map.GetWidth(); x++) 
      {
        int sample_x0 = (x / sample_period) * sample_period;
        int sample_x1 = (sample_x0 + sample_period) % noise_map.GetWidth();
        float horizontal_blend = (x - sample_x0) * sample_frequency;

        float top = math::InterpolateCosine(base_noise_map.At(sample_x0, sample_y0),
        base_noise_map.At(sample_x1, sample_y0), horizontal_blend);

        float bottom = math::InterpolateCosine(base_noise_map.At(sample_x0, sample_y1),
        base_noise_map.At(sample_x1, sample_y1), horizontal_blend);

        noise_map.At(x, y) += math::InterpolateCosine(top, bottom, vertical_blend) * amplitude;
      }
    }
  }

  for (size_t y = 0; y < base_noise_map.GetHeight(); ++y) 
  {
    for (size_t x = 0; x < base_noise_map.GetWidth(); ++x) 
    {
      noise_map.At(x, y) /= total_amplitude;
    }
  }

  return noise_map;
}

}  // namespace feudosim