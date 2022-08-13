#include "all_positions.h"
#include "cross_positions.h"
#include "position.h"
#include "masks/horizontal_masks.h"
#include "diagonal_positions.h"
#include <cassert>
#include "tests/diagonal_positions_tests.h"
#include "constants.h"
#include "L_positions.h"
#include "one_square_forward.h"

#ifndef BOARD_H
#define BOARD_H

#define WROOK 0
#define WBISHOP 1
#define WQUEEN 2
#define WPAWN 3
#define WKNIGHT 4
#define WKING 5

#define BROOK 6
#define BBISHOP 7
#define BQUEEN 8
#define BPAWN 9
#define BKNIGHT 10
#define BKING 11

namespace Boards {
  uint64_t retrieve_occ_in_range(uint64_t boards[12], uint8_t lower, uint8_t upper);
  uint64_t retrieve_all_occ(uint64_t boards[12]);
  uint64_t retrieve_white_occ(uint64_t boards[12]);
  uint64_t retrieve_black_occ(uint64_t boards[12]);
  
  uint64_t retrieve_ally_occ(uint64_t boards[12], uint16_t turn);
  uint64_t retrieve_enemy_occ(uint64_t boards[12], uint16_t turn);

  uint64_t generate_current_moves(uint64_t boards[12], uint16_t turn);

  uint64_t retrieve_ally_attack_map(uint64_t boards[12], uint16_t turn);
  uint64_t retrieve_enemy_attack_map(uint64_t boards[12], uint16_t turn);
  uint64_t retrieve_ally_defend_map(uint64_t boards[12], uint16_t turn);
  uint64_t retrieve_ally_defend_map(uint64_t boards[12], uint16_t turn);
}

#endif