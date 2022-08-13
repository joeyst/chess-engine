#include <cstdint>
#include "board.h"
#include <array>
#include "pawn_move_generation.h"
#include "L_positions.h"
#include "move_generation_utility.h"
#include "constants.h"
#include "knight_move_generation.h"

#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

namespace GenerateMoves {
  namespace Rook {
    vector<ARRAY_OF_BOARDS> generate_rook_states_generic(ARRAY_OF_BOARDS bitmaps, uint8_t layer, uint8_t team, uint64_t occ, uint64_t ally_occ); 
  }
}

#endif