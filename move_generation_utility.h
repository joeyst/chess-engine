#include <cstdint>
#include <array>
#include <vector>
#include <cmath>
#include "constants.h"
#include "masks/horizontal_masks.h"

#ifndef MOVE_GENERATION_UTILITY_H
#define MOVE_GENERATION_UTILITY_H

using namespace std;

namespace GenerateMoves {
  vector<uint64_t> split_moves_into_separate_boards(uint64_t potential_moves);
  ARRAY_OF_BOARDS remove_taken_piece(uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team);
  ARRAY_OF_BOARDS update_piece(uint64_t start, uint64_t finish, ARRAY_OF_BOARDS bitmaps, uint8_t team, uint8_t layer_of_piece);
  
  uint64_t cross_mask_from_square(uint8_t square);
  uint64_t diag_mask_from_square(uint8_t square); 
  uint64_t cross_occ(uint8_t square, uint64_t board);
  uint64_t diag_occ(uint8_t square, uint64_t board);
}
#endif