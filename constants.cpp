#include "constants.h"
#include <iostream>

uint64_t isolate_lsb(uint64_t board) {
  return (board & -board);
}

uint64_t isolate_msb(uint64_t board) {
  uint64_t last_before_zero = 0;
  if (board == 0) return 0;
  while (board) {
    last_before_zero = board;
    board &= (board - 1);
  }
  return last_before_zero;
}

uint64_t value_from_square(uint8_t square) {
  uint64_t b = 1;
  return (uint64_t)(b << square);
}

uint64_t all_but_index(uint8_t square) {
  uint64_t value_from_index = value_from_square(square);
  return (WHOLE_BOARD ^ value_from_index);
}

namespace Masks {
  uint64_t mask_of_given_file(uint8_t file) {
    uint64_t board = FIRST_VERTICAL;
    return (board << file);
  }

  uint64_t mask_of_given_rank(uint8_t rank) {
    uint64_t board = FIRST_HORIZONTAL;
    return (board << (rank * 8));
  }

  uint64_t mask_to_left_of_square(uint8_t square) {
    uint8_t rank = (square / 8);
    uint8_t file = (square % 8);
    if (file == 0) return 0;
    uint64_t pushed_horizontal = (mask_of_given_rank(rank) >> (8 - file));
    return (pushed_horizontal & mask_of_given_rank(rank));
  }

  uint64_t mask_to_right_of_square(uint8_t square ){
    uint8_t rank = (square / 8);
    uint8_t file = (square % 8);
    if (file == 7) return 0;
    uint64_t pushed_horizontal = (mask_of_given_rank(rank) << (file + 1));
    return (pushed_horizontal & mask_of_given_rank(rank));
  } 

  uint64_t mask_above_of_square(uint8_t square) {
    uint8_t rank = (square / 8);
    uint8_t file = (square % 8);
    if (rank == 7) return 0;
    uint64_t pushed_vertical = (mask_of_given_file(file) << ((rank + 1) * 8));
    return (pushed_vertical & mask_of_given_file(file));
  }

  uint64_t mask_below_of_square(uint8_t square) {
    uint8_t rank = (square / 8);
    uint8_t file = (square % 8);
    if (rank == 0) return 0;
    uint64_t pushed_vertical = (mask_of_given_file(file) >> ((8 - rank) * 8));
    return (pushed_vertical & mask_of_given_file(file));
  }
  
  uint64_t mask_of_cross_outside_of_square(uint8_t square) {
    uint8_t rank = (square / 8);
    uint8_t file = (square % 8);
    return (mask_of_given_rank(rank) ^ mask_of_given_file(file));
  }
}
