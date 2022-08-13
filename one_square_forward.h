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

#ifndef TWO_SQUARES_FORWARD
#define TWO_SQUARES_FORWARD
namespace TwoSqrs {
  uint64_t calculate_moves_two_up(uint64_t starting_pawns, uint64_t board);
  uint64_t calculate_moves_two_down(uint64_t starting_pawns, uint64_t board);
}

#endif

#ifndef FORWARD_AND_RIGHT
#define FORWARD_AND_RIGHT

namespace ForwardAndToSide {
  uint64_t calculate_moves_right_and_up(uint64_t starting_pawns, uint64_t enemies);
  uint64_t calculate_moves_right_and_down(uint64_t starting_pawns, uint64_t enemies);
  uint64_t calculate_moves_left_and_up(uint64_t starting_pawns, uint64_t enemies);
  uint64_t calculate_moves_left_and_down(uint64_t starting_pawns, uint64_t enemies);
}

#endif

#ifndef SQUARE_MOVES
#define SQUARE_MOVES

namespace SquareMoves {
  uint64_t calculate_square_moves(uint64_t square);
}

#endif