#include "include_files.h"

using namespace std;

#ifndef QUEEN_MOVE_GENERATION_H
#define QUEEN_MOVE_GENERATION_H

namespace GenerateMoves {

  namespace Queen {
    vector<ARRAY_OF_BOARDS> generate_wqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
    vector<ARRAY_OF_BOARDS> generate_bqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice); 
  }

}

#endif