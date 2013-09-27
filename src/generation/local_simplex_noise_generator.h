#ifndef FEUDOSIM_GENERATION_LOCAL_SIMPLEX_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_LOCAL_SIMPLEX_NOISE_GENERATOR_H_

#include "generation/local_noise_generator.h"
#include "helpers/vector2.h"

#include <random>
#include <vector>

namespace feudosim 
{

class LocalSimplexNoiseGenerator : public LocalNoiseGenerator
{
 public:
  LocalSimplexNoiseGenerator();
  ~LocalSimplexNoiseGenerator();

  void Seed();
  double Generate(double x, double y);

 private:  
  void FillOrientationTables();
  void FillPermutationTables();

  size_t GetOrientationPosFromTable(const Vector2<size_t> &position);

  std::default_random_engine random_engine_; 

  size_t orientation_count_;
  std::vector< Vector2<double> > orientations_;
  size_t permutation_count_;
  std::vector<size_t> permutations_;
};

}  // namespace feudosim

#endif  // FEUDOSIM_GENERATION_LOCAL_SIMPLEX_NOISE_GENERATOR_H_