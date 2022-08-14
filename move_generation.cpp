#include "move_generation.h"
#include "pawn_move_generation.h"
#include "L_positions.h"
#include <cmath>
#include "move_generation_utility.h"
#include <vector>
#include "constants.h"
#include "knight_move_generation.h"
#include "rook_move_generation.h"
#include "bishop_move_generation.h"
#include "king_move_generation.h"
#include "board.h"
#include "queen_move_generation.h"

using namespace std;

namespace GenerateMoves {

  vector<ARRAY_OF_BOARDS> wstates(ARRAY_OF_BOARDS bitmaps) {
    vector<ARRAY_OF_BOARDS> states = {};
    uint64_t ally_occ = Boards::retrieve_white_occ(bitmaps);
    uint64_t occ = Boards::retrieve_all_occ(bitmaps);
    uint8_t team = WHITE;

    for (auto state : Rook::generate_wrook_states(bitmaps, occ, ally_occ, bitmaps[WROOK])) states.push_back(state);
    for (auto state : Queen::generate_wqueen_states(bitmaps, occ, ally_occ, bitmaps[WQUEEN])) states.push_back(state);
    for (auto state : Bishop::generate_wbishop_states(bitmaps, occ, ally_occ, bitmaps[WBISHOP])) states.push_back(state);
    for (auto state : Knight::generate_wknight_states(bitmaps[WKNIGHT], ally_occ, bitmaps)) states.push_back(state);
    for (auto state : Pawn::generate_wpawn_states(bitmaps)) states.push_back(state);
    for (auto state : King::generate_wking_states(bitmaps, bitmaps[WKING], ally_occ)) states.push_back(state);

    return states;
  }

  vector<ARRAY_OF_BOARDS> bstates(ARRAY_OF_BOARDS bitmaps) {
    vector<ARRAY_OF_BOARDS> states = {};
    uint64_t ally_occ = Boards::retrieve_black_occ(bitmaps);
    uint64_t occ = Boards::retrieve_all_occ(bitmaps);
    uint8_t team = BLACK;

    for (auto state : Rook::generate_brook_states(bitmaps, occ, ally_occ, bitmaps[BROOK])) states.push_back(state);
    for (auto state : Queen::generate_bqueen_states(bitmaps, occ, ally_occ, bitmaps[BQUEEN])) states.push_back(state);
    for (auto state : Bishop::generate_bbishop_states(bitmaps, occ, ally_occ, bitmaps[BBISHOP])) states.push_back(state);
    for (auto state : Knight::generate_bknight_states(bitmaps[BKNIGHT], ally_occ, bitmaps)) states.push_back(state);
    for (auto state : Pawn::generate_bpawn_states(bitmaps)) states.push_back(state);
    for (auto state : King::generate_bking_states(bitmaps, bitmaps[BKING], ally_occ)) states.push_back(state);

    return states;
  }

}