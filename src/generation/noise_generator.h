#ifndef FEUDOSIM_GENERATION_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_NOISE_GENERATOR_H_

#include "map/array2d.h"

#include <cstddef>

namespace feudosim 
{

class NoiseGenerator 
{
 public:
  NoiseGenerator() { }
  ~NoiseGenerator() { }

 private:  
  virtual Array2D<float> Generate(size_t width, size_t height) = 0;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_NOISE_GENERATOR_H_