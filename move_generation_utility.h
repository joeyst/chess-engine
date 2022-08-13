#include <cstdint>
#include <array>
#include <vector>
#include <cmath>
#include "constants.h"

#ifndef MOVE_GENERATION_UTILITY_H
#define MOVE_GENERATION_UTILITY_H

using namespace std;

namespace GenerateMoves {
  vector<uint64_t> split_moves_into_separate_boards(uint64_t potential_moves);
  ARRAY_OF_BOARDS remove_taken_piece(uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team);
  ARRAY_OF_BOARDS update_piece(uint64_t start, uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team, uint8_t layer_of_piece); 
}
#endif