#include <cstdint>
#include <vector>
#include <array>
#include "constants.h"
#include "move_generation_utility.h"

#ifndef PAWN_MOVE_GENERATION_H
#define PAWN_MOVE_GENERATION_H

using namespace std;
namespace GenerateMoves {
  namespace Pawn {
    namespace {
      uint64_t positive_or_negative_board_shift(uint64_t board, uint8_t shift);
      int team_number_to_board(int team);
      vector<ARRAY_OF_BOARDS> update_pawns_on_board(ARRAY_OF_BOARDS old_board, vector<ARRAY_OF_BOARDS> new_pawn_locations, int offset);
      vector<ARRAY_OF_BOARDS> clear_taken_piece(vector<ARRAY_OF_BOARDS> states, int team);
      
      vector<array<uint64_t, 12>> generate_pawn_states_generic(ARRAY_OF_BOARDS boards, uint64_t (*f) (uint64_t pawns, uint64_t occ), int offset, int team, uint64_t (*retrieve) (ARRAY_OF_BOARDS));
      vector<array<uint64_t, 12>> generate_wpawn_one_forward_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_wpawn_two_forward_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_bpawn_one_forward_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_bpawn_two_forward_states(array<uint64_t, 12> boards);

      vector<array<uint64_t, 12>> generate_wpawn_left_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_wpawn_right_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_wpawn_left_states(array<uint64_t, 12> boards);
      vector<array<uint64_t, 12>> generate_wpawn_right_states(array<uint64_t, 12> boards);
    }

    vector<array<uint64_t, 12>> generate_wpawn_states(array<uint64_t, 12> boards);
    vector<array<uint64_t, 12>> generate_bpawn_states(array<uint64_t, 12> boards);
  }
}

#endif