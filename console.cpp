#include "console.h"
#include <cmath>

using namespace std;

void print_board_with_letters(ARRAY_OF_BOARDS bitmaps) {
  unordered_map<uint8_t, uint8_t> squares_and_pieces = {};
  uint64_t current_map;

  for (int layer = 0; layer < 12; layer++) {
    current_map = bitmaps[layer];
    while (current_map) {
      squares_and_pieces[log2(current_map & -current_map)] = layer;
      current_map &= (current_map - 1);
    }
  }

  unordered_map<uint8_t, char> layer_to_letter = {
    {WPAWN, 'W'}, 
    {WROOK, 'R'},
    {WKNIGHT, 'N'},
    {WBISHOP, 'B'},
    {WQUEEN, 'Q'},
    {WKING, 'K'},
    {BPAWN, 'w'}, 
    {BROOK, 'r'},
    {BKNIGHT, 'n'},
    {BBISHOP, 'b'},
    {BQUEEN, 'q'},
    {BKING, 'k'}
  };

  // start at top rank
  // start at bottom file

  string board = "";
  uint8_t square;
  
  for (int rank = 7; rank >= 0; rank--) {
    board += "\n";
    board += to_string(rank);
    board += "  ";
    for (int file = 0; file < 8; file++) {
      square = ((rank * 8) + file);
      if (squares_and_pieces.count(square)) {
        board += layer_to_letter[squares_and_pieces[square]];
      } else {
        board += " ";
      }
      board += " ";
    }
  }
  board += "\n\n   0 1 2 3 4 5 6 7\n\n\n";
  cout << board.size();
  cout << board;
}