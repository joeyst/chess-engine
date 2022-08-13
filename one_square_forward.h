#include <cstdint>
#include "constants.h"

#ifndef ONE_SQUARE_FORWARD_H
#define ONE_SQUARE_FORWARD_H

namespace OneSqr {
  uint64_t generate_one_square_up(uint64_t board);
  uint64_t generate_one_square_down(uint64_t board);

  uint64_t calculate_moves_one_forward(uint64_t starting_pawns, uint64_t board, uint64_t (*transform) (uint64_t));
  uint64_t calculate_moves_one_up(uint64_t starting_pawns, uint64_t board);
  uint64_t calculate_moves_one_down(uint64_t starting_pawns, uint64_t board);
}

#endif

#ifndef TWO_SQUARES_FORWARD_H
#define TWO_SQUARES_FORWARD_H
namespace TwoSqrs {
  uint64_t calculate_moves_two_up(uint64_t starting_pawns, uint64_t board);
  uint64_t calculate_moves_two_down(uint64_t starting_pawns, uint64_t board);
}

#endif