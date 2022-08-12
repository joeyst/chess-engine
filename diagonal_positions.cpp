#include "diagonal_positions.h"
#include "mask.h"

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

uint64_t Diagonal::normalize_up_right(uint64_t board, uint8_t square) {
  signed int dif = ((square % 8) - (square / 8));
  if (dif == 0) {
    return board;
  }
  // in top left, shift right
  else if (dif < 0) {
    return (board << dif);
  }
  else if (dif > 0) {
    return (board >> dif);
  }
  return board;
}

uint64_t Diagonal::normalize_up_left(uint64_t board, uint8_t square) {
  signed int dif = (((square % 8) + (square / 8)) - 7);
  if (dif == 0) {
    return board;
  }
  else if (dif < 0) {
    return (board << dif);
  }
  else if (dif > 0) {
    return (board >> dif);
  }
  return board;
}

uint64_t Diagonal::mask_up_right(uint8_t square) {
  auto c = Diagonal::get_up_right_mask(square);
  auto file = (square % 8);
  auto up_and_right = Mask::fill_to_right(file);
  return (c & up_and_right);
}

uint64_t Diagonal::mask_up_left(uint8_t square) {
  auto c = Diagonal::get_up_left_mask(square);
  auto file = (square % 8);
  auto up_and_left = Mask::fill_to_left(file);
  return (c & up_and_left);
}

uint64_t Diagonal::mask_down_right(uint8_t square) {
  auto c = Diagonal::get_up_left_mask(square);
  auto file = (square % 8);
  auto down_and_right = Mask::fill_to_right(file);
  return (c & down_and_right);
}

uint64_t Diagonal::mask_down_left(uint8_t square) {
  auto c = Diagonal::get_up_right_mask(square);
  auto file = (square % 8);
  auto down_and_left = Mask::fill_to_left(file);
  return (c & down_and_left);
}

DiagonalSituation::DiagonalSituation(uint64_t b, uint8_t s) : board(b), square(s){}

uint8_t DiagonalSituation::get_file() {
  return (this->square % 8);
}
uint8_t DiagonalSituation::get_rank() {
  return (this->square / 8);
}

uint8_t DiagonalSituation::get_up_right_diagonal_number() {
  return ((this->get_file()) - (this->get_rank()));
}

uint8_t DiagonalSituation::get_up_left_diagonal_number() {
  return (7 - (this->get_file() + this->get_rank()));
}

uint64_t DiagonalSituation::get_occ_to_up_right() {
  auto b = this->board;
  auto mask = Diagonal::get_up_right_mask(this->square);
  b &= mask;
  b &= Mask::fill_to_right(1);

}