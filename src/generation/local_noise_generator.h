#ifndef FEUDOSIM_GENERATION_LOCAL_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_LOCAL_NOISE_GENERATOR_H_

namespace feudosim 
{

class LocalNoiseGenerator 
{
 public:
  virtual double Generate(double x, double y) = 0;
  virtual void Seed() = 0;
  
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_LOCAL_NOISE_GENERATOR_H_