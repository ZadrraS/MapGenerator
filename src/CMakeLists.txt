include_directories(.)

add_definitions(-Wall -Wextra -W -ggdb -std=c++11)

include_directories()
link_libraries(
  sfml-graphics
  sfml-window
  sfml-system
)

add_executable(feudosim
  main.cpp

  generation/fractal_noise_generator.cpp
  generation/fractal_simplex_noise_generator.cpp
  generation/fractal_value_noise_generator.cpp
  generation/poisson_point_sampler.cpp
  generation/terrain_generator.cpp

  helpers/sfml_conversion.cpp
)

install(TARGETS feudosim DESTINATION bin)