#include "evaluation_functions.h"
#include "minimax.h"
#include "constants.h"
#include <vector>
#include <array>
#include "move_generation.h"
#include "console.h"

namespace EvaluationFunction {

  namespace {
    array<int16_t, 12> points_per_piece{5, 3, 9, 1, 3, 100, -5, -3, -9, -1, -3, -100};
  }

  int16_t simple_count_of_points(ARRAY_OF_BOARDS state) {
    array<uint8_t, 12> count = piece_count(state);
    int16_t points = 0;
    int16_t current_points;

    for (int slice_index = 0; slice_index < 12; slice_index++) {
      current_points = count_pieces_on_slice(state[slice_index]);
      points += (current_points * points_per_piece[slice_index]);
    }
    return points;
  }

}