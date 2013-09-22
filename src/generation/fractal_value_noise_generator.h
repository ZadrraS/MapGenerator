#ifndef FEUDOSIM_GENERATION_FRACTAL_VALUE_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_FRACTAL_VALUE_NOISE_GENERATOR_H_

#include "map/array2d.h"
#include "generation/fractal_noise_generator.h"

#include <random>

namespace feudosim 
{

class FractalValueNoiseGenerator : public FractalNoiseGenerator
{
 public:
  FractalValueNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity);
  ~FractalValueNoiseGenerator();

  Array2D<float> Generate(size_t width, size_t height);

 private:  
  std::default_random_engine random_engine_;

};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_FRACTAL_VALUE_NOISE_GENERATOR_H_