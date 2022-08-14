#include "move_generation_utility.h"
#include "board.h"

#ifndef BISHOP_MOVE_GENERATION_H
#define BISHOP_MOVE_GENERATION_H

namespace GenerateMoves {
  namespace Bishop {
      vector<ARRAY_OF_BOARDS> generate_bishop_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t layer, uint8_t team, uint64_t occ, uint64_t ally_occ, uint8_t index_of_layer); 
      vector<ARRAY_OF_BOARDS> generate_wbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice, uint8_t index_slice = WBISHOP); 
      vector<ARRAY_OF_BOARDS> generate_bbishop_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice, uint8_t index_slice = BBISHOP); 
  }
}

#endif