#include "move_generation_utility.h"
#include <cstdint>
#include <vector>
#include "constants.h"
#include "diagonal_positions.h"
#include "board.h"

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

  ARRAY_OF_BOARDS override_other_occupation(uint8_t attacking_team, ARRAY_OF_BOARDS bitmaps) {
    uint64_t attacker_occ = 0;
    uint64_t all_but_attacker_occ = 0;
    if (attacking_team == WHITE) {
      attacker_occ = Boards::retrieve_white_occ(bitmaps);
      all_but_attacker_occ = (attacker_occ ^ WHOLE_BOARD);
      for (int board_index = 6; board_index < 12; board_index++) {
        bitmaps[board_index] &= all_but_attacker_occ;
      }
      return bitmaps;
    } 
    else if (attacking_team == BLACK) {
      attacker_occ = Boards::retrieve_black_occ(bitmaps);
      all_but_attacker_occ = (attacker_occ ^ WHOLE_BOARD);
      for (int board_index = 0; board_index < 6; board_index++) {
        bitmaps[board_index] &= all_but_attacker_occ;
      }
      return bitmaps;
    } 
    else {
      throw logic_error("move_generation_utility.cpp override_other_occupation, neither team passed in.");
    }

  }

  ARRAY_OF_BOARDS update_piece(uint64_t start, uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team, uint8_t layer_of_piece) {
    ARRAY_OF_BOARDS with_removed_piece = remove_taken_piece(finish, bitmaps, team);
    with_removed_piece[layer_of_piece] ^= (start | finish);
    return with_removed_piece;
  }

  uint64_t cross_mask_from_square(uint8_t square) {
    return Masks::mask_of_cross_outside_of_square(square);
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

  uint64_t crop_board(uint8_t square, uint64_t board) {
    uint64_t cross_board = board;
    int file = (square % 8);
    int rank = (square / 8);
    if (file != 0) {
      cross_board &= ALL_BUT_FIRST_VERTICAL;
    } 
    if (file != 7) {
      cross_board &= ALL_BUT_LAST_VERTICAL;
    }
    if (rank != 0) {
      cross_board &= ALL_BUT_FIRST_HORIZONTAL;
    }
    if (rank != 7) {
      cross_board &= ALL_BUT_LAST_HORIZONTAL;
    }
    return cross_board;
  }

  uint64_t cross_occ_cropped(uint8_t square, uint64_t board) {
    return crop_board(square, cross_occ(square, board));
  }

  uint64_t diag_occ_cropped(uint8_t square, uint64_t board) {
    return crop_board(square, diag_occ(square, board));
  }
}
