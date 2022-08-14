#include "include_files.h"
#include "king_move_generation.h"
#include "board.h"
#include "move_generation_utility.h"

using namespace std;
using namespace GenerateMoves;

namespace GenerateMoves {

  namespace King {

    vector<ARRAY_OF_BOARDS> generate_king_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint8_t index_of_slice, uint64_t ally_occ, uint8_t team) {
      vector<ARRAY_OF_BOARDS> states = {};
      if (square == 0) return states;
      uint8_t square_number = log2(square);
      ARRAY_OF_BOARDS temp_state;
      uint64_t square_moves = SquareMoves::calculate_square_moves(log2(square));
      uint64_t ally_vacant = (ally_occ ^ WHOLE_BOARD);
      uint64_t valid_square_moves = (ally_vacant & square_moves);

      vector<uint64_t> possible_squares = split_moves_into_separate_boards(valid_square_moves);
      for (auto finish_square : possible_squares) {
        temp_state = update_piece(square, finish_square, bitmaps, team, index_of_slice);
        states.push_back(temp_state);
      }
      return states;
    }

    vector<ARRAY_OF_BOARDS> generate_wking_states(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint64_t ally_occ) {
      return generate_king_states_generic(bitmaps, square, WKING, ally_occ, WHITE);
    } 

    vector<ARRAY_OF_BOARDS> generate_bking_states(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint64_t ally_occ) {
      return generate_king_states_generic(bitmaps, square, BKING, ally_occ, BLACK);
    }

  }
}