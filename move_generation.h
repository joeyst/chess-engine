#include <cstdint>
#include "board.h"
#include <array>

#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

namespace GenerateMoves {
  namespace {
    int team_number_to_board(int team);
    vector<uint64_t> split_moves_into_separate_boards(uint64_t potential_moves);
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

}

#endif