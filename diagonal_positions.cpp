#include "diagonal_positions.h"

uint64_t get_up_right_mask(uint8_t square) {
  signed int dif = ((square / 8) - (square % 8));
  uint64_t mask = UP_RIGHT_DIAGONAL;

  if (dif == 0) {
    return mask;
  } 
  
  // in bottom right half of board
  else if (dif < 0) {
    for (int i = 0; i > dif; i--) {
      mask &= ALL_BUT_LAST_VERTICAL;
      mask <<= 1;
    }
  }

  // in top left half of board
  else if (dif > 0) {
    for (int i = 0; i < dif; i++) {
      mask &= ALL_BUT_FIRST_VERTICAL;
      mask >>= 1;
    }
  }
  return mask;
}

uint64_t get_up_left_mask(uint8_t square) {
  signed int dif = (7 - ((square % 8) + (square / 8)));
  uint64_t mask = UP_LEFT_DIAGONAL;

  if (dif == 0) {
    return mask;
  } 
  
  // in top right half of board
  else if (dif < 0) {
    for (int i = 0; i > dif; i--) {
      mask &= ALL_BUT_LAST_VERTICAL;
      mask <<= 1;
    }
  }

  // in bottom left half of board
  else if (dif > 0) {
    for (int i = 0; i < dif; i++) {
      mask &= ALL_BUT_FIRST_VERTICAL;
      mask >>= 1;
    }
  }
  return mask;
}