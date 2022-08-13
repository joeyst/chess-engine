#include "include_files.h"

#ifndef KING_MOVE_GENERATION_H
#define KING_MOVE_GENERATION_H

using namespace std;

namespace GenerateMoves {

  namespace King {

    vector<ARRAY_OF_BOARDS> generate_king_states_generic(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint8_t index_of_slice, uint64_t ally_occ, uint8_t team); 
    vector<ARRAY_OF_BOARDS> generate_wking_states(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint64_t ally_occ); 
    vector<ARRAY_OF_BOARDS> generate_bking_states(ARRAY_OF_BOARDS bitmaps, uint64_t square, uint64_t ally_occ); 

  }

}

#endif