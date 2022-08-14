#include <cstdint>
#include "board.h"
#include <array>
#include "pawn_move_generation.h"
#include "L_positions.h"
#include "move_generation_utility.h"
#include "constants.h"
#include "knight_move_generation.h"
#include "rook_move_generation.h"
#include "king_move_generation.h"

#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H

namespace GenerateMoves {

  vector<ARRAY_OF_BOARDS> wstates(ARRAY_OF_BOARDS bitmaps);
  vector<ARRAY_OF_BOARDS> bstates(ARRAY_OF_BOARDS bitmaps);

}

#endif