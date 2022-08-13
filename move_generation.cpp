#include "move_generation.h"
#include "pawn_move_generation.h"
#include "L_positions.h"
#include <cmath>
#include "move_generation_utility.h"
#include <vector>
#include "constants.h"

namespace GenerateMoves {
  namespace Knight {
      
    namespace {
      uint8_t get_layer_from_team(int team) {
        if (team == WHITE) {
          return WKNIGHT;
        } else if (team == BLACK) {
          return BKNIGHT;
        } else {
          throw logic_error("GenerateMoves::Knight::(anonymous namespace)::get_layer_from_team, neither white nor black team.");
        }
      }

      uint64_t can_move_to(uint64_t board_with_knight, int team, uint64_t ally_occ) {
        uint8_t square = log2(board_with_knight);
        uint64_t L_of_moves = L_shape::generate_L_from_square(square);
        return (L_of_moves & (ally_occ ^ WHOLE_BOARD));
      }

      vector<uint64_t> generate_knight_states_for_one_knight_unupdated(uint64_t specific_knight, int team, uint64_t ally_occ) {
        vector<uint64_t> states = {};
        uint64_t result = can_move_to(specific_knight, team, ally_occ);
        return split_moves_into_separate_boards(result);
      }

      vector<ARRAY_OF_BOARDS> generate_knight_states_for_one_knight_updated(uint64_t specific_knight, int team, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps) {
        vector<ARRAY_OF_BOARDS> states = {};
        vector<uint64_t> can_move_to_squares = generate_knight_states_for_one_knight_unupdated(specific_knight, team, ally_occ);
        for (auto s : can_move_to_squares) {
          auto a = update_piece(specific_knight, s, bitmaps, team, get_layer_from_team(team));
          states.push_back(a);
        }
        return states;
      }

      vector<ARRAY_OF_BOARDS> generate_knight_states_generic(uint64_t knights, int team, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps) {
        vector<ARRAY_OF_BOARDS> states = {};
        vector<uint64_t> specific_knights = split_moves_into_separate_boards(knights);
        for (auto knight : specific_knights) {
          for (auto c : generate_knight_states_for_one_knight_updated(knight, team, ally_occ, bitmaps)) {
            states.push_back(c);
          }
        }
        return states;
      }
    }

    vector<ARRAY_OF_BOARDS> generate_bknight_states(uint64_t knights, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps) {
      return generate_knight_states_generic(knights, BLACK, ally_occ, bitmaps);
    }

    vector<ARRAY_OF_BOARDS> generate_wknight_states(uint64_t knights, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps) {
      return generate_knight_states_generic(knights, WHITE, ally_occ, bitmaps);
    }
  }
}