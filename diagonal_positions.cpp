#include "diagonal_positions.h"
#include "mask.h"
#include <stdexcept>
#include "constants.h"
#include <cmath>

using namespace Mask;
using namespace Diagonal;

signed int Diagonal::get_up_right_diagonal_number(uint8_t square) {
  signed int dif = ((square / 8) - (square % 8));
  return dif;
}

signed int Diagonal::get_inverted_up_right_diagonal_number(uint8_t square) {
  signed int dif = ((square % 8) - (square / 8));
  return dif;
}

signed int Diagonal::get_up_left_diagonal_number(uint8_t square) {
  signed int dif = (7 - ((square % 8) + (square / 8)));
  return dif;
}

signed int Diagonal::get_inverted_up_left_diagonal_number(uint8_t square) {
  signed int dif = (((square % 8) + (square / 8)) - 7);
  return dif;
}

uint64_t Diagonal::get_a_diagonal_mask(signed int (*diag_calculator) (uint8_t), uint8_t square) {
  signed int dif = diag_calculator(square);
  uint64_t mask = 0;
  if (diag_calculator(0) == 0) {
    mask = UP_RIGHT_DIAGONAL;
  } else if (diag_calculator(0) == 7) {
    mask = UP_LEFT_DIAGONAL;
  } else {
    throw std::logic_error("Neither diagonal nor antidiagonal.");
  }
  if (dif == 0) {
    return mask;
  }

  // needs shifted right
  else if (dif < 0) {
    for (int i = 0; i > dif; i--) {
      mask &= ALL_BUT_LAST_VERTICAL;
      mask <<= 1;
    }
  }

  // needs shifted left
  else if (dif > 0) {
    for (int i = 0; i < dif; i++) {
      mask &= ALL_BUT_FIRST_VERTICAL;
      mask >>= 1;
    }
  }
  return mask;
}

uint64_t Diagonal::get_up_left_mask(uint8_t square) {
  return Diagonal::get_a_diagonal_mask(get_up_left_diagonal_number, square);
}

uint64_t Diagonal::get_up_right_mask(uint8_t square) {
  return Diagonal::get_a_diagonal_mask(get_up_right_diagonal_number, square);
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

uint64_t Diagonal::mask_to_direction(uint64_t (*diag) (uint8_t), uint64_t (*fill_direction) (uint8_t), uint8_t square) {
  auto c = diag(square);
  auto file = (square % 8);
  auto partial_mask = fill_direction(file);
  return (c & partial_mask);
}

uint64_t Diagonal::mask_up_right(uint8_t square) {
  return (mask_to_direction(get_up_right_mask, fill_to_right, square));
}

uint64_t Diagonal::mask_up_left(uint8_t square) {
  return (mask_to_direction(get_up_left_mask, fill_to_left, square));
}

uint64_t Diagonal::mask_down_right(uint8_t square) {
  return (mask_to_direction(get_up_left_mask, fill_to_right, square));
}

uint64_t Diagonal::mask_down_left(uint8_t square) {
  return (mask_to_direction(get_up_right_mask, fill_to_left, square));
}

uint64_t Diagonal::mask_to_all_diag_excluding_own_square(uint8_t square) {
  return (mask_up_right(square) | mask_up_left(square) | mask_down_right(square) | mask_down_left(square));
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

uint64_t DiagonalSituation::get_occ_to_direction(uint64_t (*mask_of_square) (uint8_t)) {
  auto b = this->board;
  auto mask = mask_of_square(this->square);
  b &= mask;
  return b;
}

uint64_t DiagonalSituation::get_occ_to_up_right() {
  return this->get_occ_to_direction(mask_up_right);
}

uint64_t DiagonalSituation::get_occ_to_down_left() {
  return this->get_occ_to_direction(mask_down_left);
}

uint64_t DiagonalSituation::get_occ_to_up_left() {
  return this->get_occ_to_direction(mask_up_left);
}

uint64_t DiagonalSituation::get_occ_to_down_right() {
  return this->get_occ_to_direction(mask_down_right);
}

uint64_t DiagonalSituation::get_blocked_to_up_right() {
  auto b = this->get_occ_to_up_right();
  auto bit = isolate_lsb(b);
  if (bit == 0) return 0;
  return (Diagonal::mask_up_right(log2(bit)));
}

uint64_t DiagonalSituation::get_blocked_to_up_left() {
  auto b = this->get_occ_to_up_left();
  auto bit = isolate_lsb(b);
  if (bit == 0) return 0;
  return (Diagonal::mask_up_left(log2(bit)));
}

uint64_t DiagonalSituation::get_blocked_to_down_right() {
  auto b = this->get_occ_to_down_right();
  auto bit = isolate_msb(b);
  if (bit == 0) return 0;
  return (Diagonal::mask_down_right(log2(bit)));
}

uint64_t DiagonalSituation::get_blocked_to_down_left() {
  auto b = this->get_occ_to_down_left();
  auto bit = isolate_msb(b);
  if (bit == 0) return 0;
  return (Diagonal::mask_down_left(log2(bit)));
}

uint64_t DiagonalSituation::get_blocked_in_all_diagonals() {
  auto ul = this->get_blocked_to_up_left();
  auto ur = this->get_blocked_to_up_right();
  auto dl = this->get_blocked_to_down_left();
  auto dr = this->get_blocked_to_down_right();
  return (ul | ur | dl | dr);
}