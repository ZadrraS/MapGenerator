#ifndef FEUDOSIM_GENERATION_FRACTAL_SIMPLEX_NOISE_GENERATOR_H_
#define FEUDOSIM_GENERATION_FRACTAL_SIMPLEX_NOISE_GENERATOR_H_

#include "generation/fractal_noise_generator.h"
#include "helpers/vector2.h"

#include <random>

namespace feudosim 
{

class FractalSimplexNoiseGenerator : public FractalNoiseGenerator
{
 public:
  FractalSimplexNoiseGenerator(size_t octave_count, double period, double gain, double lacunarity);
  ~FractalSimplexNoiseGenerator();

  Array2D<float> Generate(size_t width, size_t height);

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

#endif  // FEUDOSIM_GENERATION_FRACTAL_SIMPLEX_NOISE_GENERATOR_H_