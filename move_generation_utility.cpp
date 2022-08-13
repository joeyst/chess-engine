#include "move_generation_utility.h"
#include <cstdint>
#include <vector>
#include "constants.h"
#include "diagonal_positions.h"

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

  uint64_t cross_mask_from_square(uint8_t square) {
    return (Masks::mask_to_left(square % 8) | Masks::mask_to_right(square % 8) | Masks::mask_above(square / 8) | Masks::mask_below(square / 8));
  }

  uint64_t diag_mask_from_square(uint8_t square) {
    return (Diagonal::mask_up_right(square) | Diagonal::mask_up_left(square) | Diagonal::mask_down_right(square) | Diagonal::mask_down_left(square));
  }

  uint64_t cross_occ(uint8_t square, uint64_t board) {
    return (cross_mask_from_square(square) & board);
  }

  uint64_t diag_occ(uint8_t square, uint64_t board) {
    return (diag_mask_from_square(square) & board);
  }
}
