#include <array>
#include <cstdint>
#include "constants.h"


#ifndef EVALUATION_FUNCTION_H
#define EVALUATION_FUNCTION_H

namespace EvaluationFunction {

  namespace {
    extern std::array<int16_t, 12> points_per_piece;
  }

  int16_t simple_count_of_points(std::ARRAY_OF_BOARDS state);

}

#endif