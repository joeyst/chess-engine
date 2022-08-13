#include "constants.h"

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