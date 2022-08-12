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
  vector<string> horizontals = {};
  string horizontal = "";
  for (int rank = 0; rank < 8; rank++) {
    horizontal = "\n";
    horizontal += to_string(rank);
    horizontal += "   ";
    for (int file = 0; file < 8; file++) {
      horizontal += to_string(board & 1);
      horizontal += " ";
      board >>= 1;
    }
      horizontals.push_back(horizontal);
      horizontal = "";
  }

  for (int rank = 0; rank < 8; rank++) cout << horizontals[7 - rank];
  cout << endl << "\n    0 1 2 3 4 5 6 7\n\n\n";
}

int main () {
  auto hs = HorizontalSituation(1, 1);
  hs.print_board();
  hs.board = mask_to_right(5);
  hs.print_board();
  print_board(mask_to_right(5));
  return 0;
}