#ifndef FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_

#include "map/array2d.h"
#include "generation/noise_generator.h"

#include <random>

namespace feudosim 
{

class FractalNoiseGenerator : public NoiseGenerator
{
 public:
  FractalNoiseGenerator(size_t octave_count, double persistance);
  ~FractalNoiseGenerator();

  Array2D<float> Generate(size_t width, size_t height);

 private:  
  std::default_random_engine random_engine_;

  size_t octave_count_;
  double persistance_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_FRACTAL_NOISE_GENERATOR_H_