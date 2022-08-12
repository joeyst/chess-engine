#include "cross_positions.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "masks/horizontal_masks.h"
#include <cmath>
#include "position.h"

using namespace std;
using namespace Masks;

HorizontalSituation::HorizontalSituation() : board(0), file(0){}
HorizontalSituation::HorizontalSituation(uint64_t b, uint8_t f) : board(b), file(f){}
void HorizontalSituation::print_board() {
  auto temp_board = this->board;
  vector<string> horizontals = {};
  string horizontal = "";
  for (int rank = 0; rank < 8; rank++) {
    horizontal = "\n";
    horizontal += to_string(rank);
    horizontal += "   ";
    for (int temp_file = 0; temp_file < 8; temp_file++) {
      horizontal += to_string(temp_board & 1);
      horizontal += " ";
      temp_board >>= 1;
    }
      horizontals.push_back(horizontal);
      horizontal = "";
  }

  for (int rank = 0; rank < 8; rank++) cout << horizontals[7 - rank];
  cout << endl << "\n    0 1 2 3 4 5 6 7\n\n\n";
}

uint64_t HorizontalSituation::get_occ_to_right() {
  return (this->board & Masks::mask_to_right(this->file));
}

uint64_t HorizontalSituation::get_occ_to_left() {
  return (this->board & Masks::mask_to_left(this->file));
}

uint64_t HorizontalSituation::get_block_to_right() {
  auto occ_to_right = this->get_occ_to_right();
  // if none blocking, return as clear 
  if (occ_to_right == 0) return 0;
  // get check right of index of least significant bit
  return (Masks::mask_to_right(log2(occ_to_right & -occ_to_right)));
}

uint64_t HorizontalSituation::get_block_to_left() {
  auto occ_to_left = this->get_occ_to_left();
  if (occ_to_left == 0) return 0;
  return (Masks::mask_to_left(log2(occ_to_left)));
}

uint64_t HorizontalSituation::get_block_L_R() {
  return (this->get_block_to_left() | this->get_block_to_right());
}


VerticalSituation::VerticalSituation() : board(0), rank(0){}
VerticalSituation::VerticalSituation(uint64_t b, uint8_t r) : board(b), rank(r){}

uint64_t VerticalSituation::flip_board_to_horizontal() {
  auto b = this->board;
  uint64_t new_board = 0;
  for (int ranks_shifted = 0; ranks_shifted < 8; ranks_shifted++) {
    new_board <<= 1;
    if (b & TOP_SQUARE_OF_VERTICAL) {
      new_board |= 1;
    }
    b <<= 8;
  }
  return new_board;
}

uint64_t VerticalSituation::flip_board_to_vertical(uint64_t b) {
  uint64_t new_board = 0;
  for (int ranks_shifted = 0; ranks_shifted < 8; ranks_shifted++) {
    new_board <<= 8;
    if (b & LAST_SQUARE_OF_HORIZONTAL) {
      new_board |= 1;
    }
    b <<= 1;
    b &= FIRST_HORIZONTAL;
  }
  return new_board;
}



void VerticalSituation::print_board() {
  auto temp_board = this->board;
  vector<string> horizontals = {};
  string horizontal = "";
  for (int rank = 0; rank < 8; rank++) {
    horizontal = "\n";
    horizontal += to_string(rank);
    horizontal += "   ";
    for (int temp_file = 0; temp_file < 8; temp_file++) {
      horizontal += to_string(temp_board & 1);
      horizontal += " ";
      temp_board >>= 1;
    }
      horizontals.push_back(horizontal);
      horizontal = "";
  }

  for (int rank = 0; rank < 8; rank++) cout << horizontals[7 - rank];
  cout << endl << "\n    0 1 2 3 4 5 6 7\n\n\n";
}

uint64_t VerticalSituation::get_occ_above() {
  auto flipped_board = this->flip_board_to_horizontal();
  auto temp_horiz = HorizontalSituation(flipped_board, this->rank);
  auto horizontal_blockage = temp_horiz.get_block_to_right();
  return this->flip_board_to_vertical(horizontal_blockage);
}

uint64_t VerticalSituation::get_occ_below() {
  auto flipped_board = this->flip_board_to_horizontal();
  auto temp_horiz = HorizontalSituation(flipped_board, this->rank);
  auto horizontal_blockage = temp_horiz.get_block_to_left();
  return this->flip_board_to_vertical(horizontal_blockage);
}

uint64_t VerticalSituation::get_block_above() {
  auto flipped_board = this->flip_board_to_horizontal();
  auto temp_horiz = HorizontalSituation(flipped_board, this->rank);
  auto horizontal_blockage = temp_horiz.get_block_to_right();
  return this->flip_board_to_vertical(horizontal_blockage);
}

uint64_t VerticalSituation::get_block_below() {
  auto flipped_board = this->flip_board_to_horizontal();
  auto temp_horiz = HorizontalSituation(flipped_board, this->rank);
  auto horizontal_blockage = temp_horiz.get_block_to_left();
  return this->flip_board_to_vertical(horizontal_blockage);
}

uint64_t VerticalSituation::get_block_A_B() {
  return (this->get_block_above() | this->get_block_below());
}

int main () {
  auto vs = VerticalSituation(0x1000100010001, 1);
  print_board(vs.board);
  print_board(vs.flip_board_to_horizontal());
  vs.board = 0x100010001000100;
  print_board(vs.board);
  print_board(vs.flip_board_to_horizontal());
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  vs.rank = 5;
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  vs.rank = 4;
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  return 0;
}