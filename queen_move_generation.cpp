#include "include_files.h"
#include "bishop_move_generation.h"
#include "rook_move_generation.h"
#include "queen_move_generation.h"

namespace GenerateMoves {
  
  namespace Queen {

    vector<ARRAY_OF_BOARDS> generate_wqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice) {
      vector<ARRAY_OF_BOARDS> states = {};
      for (auto state : GenerateMoves::Bishop::generate_wbishop_states(bitmaps, occ, ally_occ, slice)) states.push_back(state);
      for (auto state : GenerateMoves::Rook::generate_wrook_states(bitmaps, occ, ally_occ, slice)) states.push_back(state);
      return states;
    } 

    vector<ARRAY_OF_BOARDS> generate_bqueen_states(ARRAY_OF_BOARDS bitmaps, uint64_t occ, uint64_t ally_occ, uint64_t slice) {
      vector<ARRAY_OF_BOARDS> states = {};
      for (auto state : GenerateMoves::Bishop::generate_bbishop_states(bitmaps, occ, ally_occ, slice)) states.push_back(state);
      for (auto state : GenerateMoves::Rook::generate_brook_states(bitmaps, occ, ally_occ, slice)) states.push_back(state);
      return states;
    }

  }

}