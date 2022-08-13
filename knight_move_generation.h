#include <cstdint>
#include "board.h"
#include <array>
#include "L_positions.h"
#include "move_generation_utility.h"
#include "constants.h"

#ifndef KNIGHT_MOVE_GENERATION_H
#define KNIGHT_MOVE_GENERATION_H

namespace GenerateMoves {

  namespace Knight {

    namespace {
      uint64_t can_move_to(uint64_t square, int team, uint64_t enemy_occ);
      vector<uint64_t> generate_knight_states_generic(uint64_t board_with_knights, int team, uint64_t ally_occ);
      vector<ARRAY_OF_BOARDS> generate_knight_states_for_one_knight_updated(uint64_t specific_knight, int team, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps);
      vector<ARRAY_OF_BOARDS> generate_knight_states_generic(uint64_t knight_layer, int team, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps);
    }


    
    vector<ARRAY_OF_BOARDS> generate_bknight_states(uint64_t knights, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps);
    vector<ARRAY_OF_BOARDS> generate_wknight_states(uint64_t knights, uint64_t ally_occ, ARRAY_OF_BOARDS bitmaps);

  }

}

#endif