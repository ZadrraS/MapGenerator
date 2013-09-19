#ifndef FEUDOSIM_GENERATION_PERLIN_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_PERLIN_NOISE_GENERATOR_H_

#include "map/array2d.h"

#include <random>
#include <cstddef>

namespace feudosim 
{

class PerlinNoiseGenerator 
{
 public:
  PerlinNoiseGenerator();
  ~PerlinNoiseGenerator();

  Array2D<float> Generate(size_t width, size_t height);

 private:  
  std::default_random_engine random_engine_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_PERLIN_NOISE_GENERATOR_H_