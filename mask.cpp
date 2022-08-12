#include "mask.h"
#include <cstdint>
#include "constants.h"

uint64_t Mask::fill_to_right(uint8_t file) {
  if (file == 7) return 0;
  uint64_t b = WHOLE_BOARD;
  for (int f = 0; f < file + 1; f++) {
    b &= ALL_BUT_LAST_VERTICAL;
    b <<= 1;
  }
  return b;
}

uint64_t Mask::fill_to_left(uint8_t file) {
  if (file == 0) return 0;
  uint64_t b = 0;
  for (int f = 0; f < file; f++) {
    b <<= 1;
    b |= FIRST_VERTICAL;
  }
  return b;
}