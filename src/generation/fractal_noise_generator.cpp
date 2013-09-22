#include "generation/fractal_noise_generator.h"

namespace feudosim {

FractalNoiseGenerator::FractalNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity) :
  octave_count_(octave_count),
  period_(period),
  gain_(gain),
  lacunarity_(lacunarity)
{

}

FractalNoiseGenerator::~FractalNoiseGenerator() 
{

}

}  // namespace feudosim