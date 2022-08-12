#include "horizontal_masks.h"

uint64_t Masks::mask_to_left(int file) {
  return (FIRST_HORIZONTAL >> (8 - file));
}

uint64_t Masks::mask_to_right(int file) {
  auto a = FIRST_HORIZONTAL;
  a <<= (file + 1);
  return (a & FIRST_HORIZONTAL);
}

uint64_t Masks::mask_above(int rank) {
  if (rank == 7) return 0;
  return (FIRST_VERTICAL << ((rank + 1) * 8));
}

uint64_t Masks::mask_below(int rank) {
  if (rank == 0) return 0;
  return (FIRST_VERTICAL >> ((8 - rank) * 8));
}

void Masks::print_board(uint64_t board) {
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