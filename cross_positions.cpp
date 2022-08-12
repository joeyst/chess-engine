#include "cross_positions.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "masks/horizontal_masks.h"
#include <cmath>

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

int main () {
  auto hs = VerticalSituation(0xF0, 1);
  print_board(hs.flip_board_to_horizontal());
  
  return 0;
}