#include <cstdint>
#include "board.h"
#include <array>
#include "pawn_move_generation.h"
#include "L_positions.h"
#include "move_generation_utility.h"
#include "constants.h"
#include "knight_move_generation.h"
#include "rook_move_generation.h"

#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

//vector<ARRAY_OF_BOARDS> generate_sliding_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t slice, uint8_t index_of_slice, uint64_t occ, uint64_t ally_occ); 

namespace GenerateMoves {
  namespace Bishop {
      vector<ARRAY_OF_BOARDS> generate_bishop_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t layer, uint8_t team, uint64_t occ, uint64_t ally_occ, uint8_t index_of_layer); 
      vector<ARRAY_OF_BOARDS> generate_wbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
      vector<ARRAY_OF_BOARDS> generate_bbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
  }

  namespace Queen {
      vector<ARRAY_OF_BOARDS> generate_wqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
      vector<ARRAY_OF_BOARDS> generate_bqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
  }
}

#endif