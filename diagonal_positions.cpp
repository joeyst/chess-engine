#include "diagonal_positions.h"

#ifndef LAST_SQUARE_OF_HORIZONTAL
#define LAST_SQUARE_OF_HORIZONTAL 0x80
#endif

uint64_t Diagonal::get_up_right_mask(uint8_t square) {
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

uint64_t Diagonal::get_up_left_mask(uint8_t square) {
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

uint64_t Diagonal::horizontal_to_up_right(uint64_t board) {
  uint64_t new_board = 0;
  for (int bit = 0; bit < 7; bit++) {
    if (board & LAST_SQUARE_OF_HORIZONTAL) new_board |= 1;
    board <<= 1;
    new_board <<= 9;
  }
  return new_board;
}

uint64_t Diagonal::horizontal_to_up_left(uint64_t board) {
  uint64_t new_board = 0;
  for (int bit = 0; bit < 7; bit++) {
    if (board & 1) new_board |= 1;
    board >>= 1;
    new_board <<= 7;
  }
  new_board <<= 7;
  return new_board;
}
