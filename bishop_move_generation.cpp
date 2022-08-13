#include "move_generation_utility.h"
#include "bishop_move_generation.h"
#include "all_positions.h"
#include "board.h"

namespace GenerateMoves {

  namespace Bishop {

    vector<ARRAY_OF_BOARDS> generate_bishop_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t slice, uint8_t team, uint64_t occ, uint64_t ally_occ, uint8_t index_of_layer) {
      vector<ARRAY_OF_BOARDS> states = {};
      vector<uint64_t> separated_bishops = split_moves_into_separate_boards(slice);
      uint64_t occ_on_diag;
      uint64_t open_for_move;
      uint64_t blocked_off;
      uint64_t blocked_by_own_pieces;
      uint8_t square_of_piece;

      ARRAY_OF_BOARDS possible_state;
      vector<uint64_t> separate_move_possibilities;
      for (auto bishop : separated_bishops) {
        square_of_piece = log2(bishop);
        occ_on_diag = diag_occ(square_of_piece, occ);
        if (diag_block_map.count(occ_on_diag)) {
          blocked_off = diag_block_map[occ_on_diag];
        } else {
          blocked_off = Diagonal::get_blocked_in_all_diagonals(occ, log2(bishop));
          diag_block_map[occ_on_diag] = blocked_off;
        }
        blocked_off |= ally_occ;
        blocked_off ^= WHOLE_BOARD;
        blocked_off &= diag_mask_from_square(square_of_piece);
        separate_move_possibilities = split_moves_into_separate_boards(blocked_off);

        for (auto possible_board : separate_move_possibilities) {
          possible_state = update_piece(bishop, possible_board, bitmaps, team, index_of_layer);
          states.push_back(possible_state);
        }
      }
      return states;
    }


      vector<ARRAY_OF_BOARDS> generate_wbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice) {
        return generate_bishop_states_generic(bitmaps, slice, WHITE, occ, ally_occ, WBISHOP);
      } 

      vector<ARRAY_OF_BOARDS> generate_bbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice) {
        return generate_bishop_states_generic(bitmaps, slice, BLACK, occ, ally_occ, BBISHOP);
      }
  }

}