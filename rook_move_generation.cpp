#include "move_generation_utility.h"
#include "rook_move_generation.h"

#include "move_generation.h"
#include "pawn_move_generation.h"
#include "L_positions.h"
#include <cmath>
#include "move_generation_utility.h"
#include <vector>
#include "constants.h"
#include "knight_move_generation.h"

using namespace std;

namespace GenerateMoves {

  namespace Rook {

    vector<ARRAY_OF_BOARDS> generate_rook_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t slice, uint8_t team, uint64_t occ, uint64_t ally_occ, uint8_t index_of_layer) {
      vector<ARRAY_OF_BOARDS> states = {};
      vector<uint64_t> separated_rooks = split_moves_into_separate_boards(slice);
      uint64_t occ_on_cross;
      uint64_t open_for_move;
      uint64_t blocked_off;
      uint64_t blocked_by_own_pieces;
      uint8_t square_index;

      ARRAY_OF_BOARDS possible_state;
      vector<uint64_t> separate_move_possibilities;
      for (auto rook : separated_rooks) {
        square_index = log2(rook);
        occ_on_cross = cross_occ_cropped(square_index, occ);
        blocked_off = cross_block_map_map[square_index][occ_on_cross];
        blocked_off |= ally_occ;
        blocked_off ^= WHOLE_BOARD;
        blocked_off &= cross_mask_from_square(log2(rook));
        separate_move_possibilities = split_moves_into_separate_boards(blocked_off);

        for (auto possible_board : separate_move_possibilities) {
          possible_state = update_piece(rook, possible_board, bitmaps, team, index_of_layer);
          states.push_back(possible_state);
        }
      }
      return states;
    }


    vector<ARRAY_OF_BOARDS> generate_wrook_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice, uint8_t slice_index) {
      return generate_rook_states_generic(bitmaps, slice, WHITE, occ, ally_occ, slice_index);
    }

    vector<ARRAY_OF_BOARDS> generate_brook_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice, uint8_t slice_index) {
      return generate_rook_states_generic(bitmaps, slice, BLACK, occ, ally_occ, slice_index);
    }

  }

}