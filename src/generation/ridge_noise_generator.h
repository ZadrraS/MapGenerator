#ifndef FEUDOSIM_GENERATION_RIDGE_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_RIDGE_NOISE_GENERATOR_H_

#include "generation/fractal_noise_generator.h"
#include "generation/local_simplex_noise_generator.h"
#include "helpers/vector2.h"

namespace feudosim 
{

class RidgeNoiseGenerator : public FractalNoiseGenerator
{
 public:
  RidgeNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity, double offset);
  ~RidgeNoiseGenerator();

  Array2D<float> Generate(size_t width, size_t height);

 private:  
  LocalSimplexNoiseGenerator local_noise_generator_;

  double offset_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_RIDGE_NOISE_GENERATOR_H_