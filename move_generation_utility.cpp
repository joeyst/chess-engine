#include "move_generation_utility.h"
#include <cstdint>
#include <vector>
#include "constants.h"

using namespace std;
namespace GenerateMoves {
  vector<uint64_t> split_moves_into_separate_boards(uint64_t potential_moves) {
      vector<uint64_t> boards = {};
      while (potential_moves) {
        boards.push_back(potential_moves & -potential_moves);
        potential_moves &= (potential_moves - 1);
      }
      return boards;
  }

  ARRAY_OF_BOARDS remove_taken_piece(uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team) {
    uint64_t all_but_square = (finish ^ WHOLE_BOARD);
    if (team == WHITE) {
      for (int b = 6; b < 12; b++) {
        bitmaps[b] &= all_but_square;
      }
    }
    else {
      for (int b = 0; b < 6; b++) {
        bitmaps[b] &= all_but_square;
      }
    }
    return bitmaps;
  }

  ARRAY_OF_BOARDS update_piece(uint64_t start, uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team, uint8_t layer_of_piece) {
    ARRAY_OF_BOARDS with_removed_piece = remove_taken_piece(finish, bitmaps, team);
    with_removed_piece[layer_of_piece] ^= (start | finish);
    return with_removed_piece;
  }
}