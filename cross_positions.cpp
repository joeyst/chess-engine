#include "cross_positions.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "masks/horizontal_masks.h"

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

int main () {
  auto hs = HorizontalSituation(1, 1);
  hs.print_board();
  hs.print_board();
  hs = HorizontalSituation(FIRST_HORIZONTAL, 1);
  Masks::print_board(hs.get_occ_to_right());
  hs = HorizontalSituation(0xAA, 5);
  Masks::print_board(hs.get_occ_to_right());
  return 0;
}