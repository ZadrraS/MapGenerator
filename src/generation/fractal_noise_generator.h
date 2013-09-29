#ifndef FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_

#include "helpers/array2d.h"

#include <cstddef>

namespace feudosim 
{

class FractalNoiseGenerator 
{
 public:
  FractalNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity);
  ~FractalNoiseGenerator();

  virtual Array2D<float> Generate(size_t width, size_t height) = 0;

 protected: 
  size_t octave_count_;
  double period_;
  double gain_;
  double lacunarity_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_