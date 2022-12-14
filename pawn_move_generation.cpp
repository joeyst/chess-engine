#include "pawn_move_generation.h"

#include "board.h"
#include <cstring>
#include <array>
#include <vector>
#include "constants.h"
#include "move_generation_utility.h"
#include "console.h"

using namespace std;

namespace GenerateMoves {
  namespace Pawn {
    namespace {
      uint64_t positive_or_negative_board_shift(uint64_t board, signed shift) {
        if (shift < 0) {
          return (board << -shift);
        } else if (shift > 0) {
          return (board >> shift);
        } else {
          return board;
        }
      }

      int team_number_to_board(int team) {
        if (team == WHITE) {
          return WPAWN;
        } else if (team == BLACK) {
          return BPAWN;
        } else {
          throw logic_error("Neither 0 nor 7 passed into function.");
        }
      }

      vector<ARRAY_OF_BOARDS> update_pawns_on_board(ARRAY_OF_BOARDS old_board, vector<uint64_t> new_pawn_locations, int offset, int team) {
        uint64_t previous_bit;
        ARRAY_OF_BOARDS copy_of_boards;
        vector<ARRAY_OF_BOARDS> states = {};
        uint8_t board_of_pawns = team_number_to_board(team);

        for (auto p : new_pawn_locations) {
          previous_bit = positive_or_negative_board_shift(p, offset);
          copy_of_boards = old_board;
          copy_of_boards[board_of_pawns] ^= previous_bit;
          copy_of_boards[board_of_pawns] |= p;
          states.push_back(copy_of_boards);
        }
        return states;
      }


      vector<ARRAY_OF_BOARDS> clear_taken_piece(vector<ARRAY_OF_BOARDS> states, int team) {
        int board_of_pawns = team_number_to_board(team);
        uint64_t own_state;
        uint64_t nondeletion_squares;
        
        for (auto &state : states) {
          own_state = state[board_of_pawns];
          nondeletion_squares = (own_state ^ WHOLE_BOARD);
          state = override_other_occupation(team, state);
        }
        return states;
      }

      
      vector<array<uint64_t, 12>> generate_pawn_states_generic(ARRAY_OF_BOARDS boards, uint64_t (*f) (uint64_t pawns, uint64_t occ), int offset, int team, uint64_t (*retrieve) (ARRAY_OF_BOARDS) = Boards::retrieve_all_occ) {
        int board_of_pawns = team_number_to_board(team);
        uint64_t potential_moves = f(boards[board_of_pawns], retrieve(boards));
        vector<uint64_t> pawn_boards = split_moves_into_separate_boards(potential_moves);
        vector<ARRAY_OF_BOARDS> states_without_cleared_taken_pieces = update_pawns_on_board(boards, pawn_boards, offset, team);
        return clear_taken_piece(states_without_cleared_taken_pieces, team);
      }

      vector<ARRAY_OF_BOARDS> generate_wpawn_one_forward_states(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, OneSqr::calculate_moves_one_up, 8, WHITE);
      }

      vector<ARRAY_OF_BOARDS> generate_wpawn_two_forward_states(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, TwoSqrs::calculate_moves_two_up, 16, WHITE);
      }

      vector<ARRAY_OF_BOARDS> generate_bpawn_one_forward_states(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, OneSqr::calculate_moves_one_down, -8, BLACK);
      }

      vector<ARRAY_OF_BOARDS> generate_bpawn_two_forward_states(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, TwoSqrs::calculate_moves_two_down, -16, BLACK);
      }

      vector<ARRAY_OF_BOARDS> generate_wpawn_left_state(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, ForwardAndToSide::calculate_moves_left_and_up, 7, WHITE, Boards::retrieve_black_occ);
      }

      vector<ARRAY_OF_BOARDS> generate_wpawn_right_state(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, ForwardAndToSide::calculate_moves_right_and_up, 9, WHITE, Boards::retrieve_black_occ);
      }

      vector<ARRAY_OF_BOARDS> generate_bpawn_left_state(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, ForwardAndToSide::calculate_moves_left_and_down, -9, BLACK, Boards::retrieve_white_occ);
      }

      vector<ARRAY_OF_BOARDS> generate_bpawn_right_state(ARRAY_OF_BOARDS boards) {
        return generate_pawn_states_generic(boards, ForwardAndToSide::calculate_moves_right_and_down, -7, BLACK, Boards::retrieve_white_occ);
      }

    }

    vector<array<uint64_t, 12>> generate_wpawn_states(ARRAY_OF_BOARDS boards) {
      vector<array<uint64_t, 12>> states = {};
      for (auto state : generate_wpawn_one_forward_states(boards)) states.push_back(state);
      for (auto state : generate_wpawn_two_forward_states(boards)) states.push_back(state);
      for (auto state : generate_wpawn_left_state(boards)) states.push_back(state);
      for (auto state : generate_wpawn_right_state(boards)) states.push_back(state);
      return states;
    }

    vector<array<uint64_t, 12>> generate_bpawn_states(ARRAY_OF_BOARDS boards) {
      vector<array<uint64_t, 12>> states = {};
      for (auto state : generate_bpawn_one_forward_states(boards)) states.push_back(state);
      for (auto state : generate_bpawn_two_forward_states(boards)) states.push_back(state);
      for (auto state : generate_bpawn_left_state(boards)) states.push_back(state);
      for (auto state : generate_bpawn_right_state(boards)) states.push_back(state);
      return states;
    }
  }
}