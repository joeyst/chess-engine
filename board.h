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
#include <array>

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

extern unordered_map<Board, Board> cross_block_map;
extern unordered_map<uint8_t, unordered_map<Board, Board>> cross_block_map_map;
extern unordered_map<Board, Board> diag_block_map;
extern unordered_map<uint8_t, unordered_map<Board, Board>> diag_block_map_map;

namespace Boards {
  uint64_t retrieve_occ_in_range(ARRAY_OF_BOARDS boards, uint8_t lower, uint8_t upper);
  uint64_t retrieve_all_occ(ARRAY_OF_BOARDS boards);
  uint64_t retrieve_white_occ(ARRAY_OF_BOARDS boards);
  uint64_t retrieve_black_occ(ARRAY_OF_BOARDS boards);
  
  uint64_t retrieve_ally_occ(ARRAY_OF_BOARDS boards, uint16_t turn);
  uint64_t retrieve_enemy_occ(ARRAY_OF_BOARDS boards, uint16_t turn);

  vector<uint64_t> generate_wboard_states(ARRAY_OF_BOARDS boards);
  vector<uint64_t> generate_bboard_states(ARRAY_OF_BOARDS boards);
  vector<uint64_t> generate_board_states(ARRAY_OF_BOARDS boards, uint16_t turn);

  uint64_t retrieve_ally_attack_map(ARRAY_OF_BOARDS boards, uint16_t turn);
  uint64_t retrieve_enemy_attack_map(ARRAY_OF_BOARDS boards, uint16_t turn);
  uint64_t retrieve_ally_defend_map(ARRAY_OF_BOARDS boards, uint16_t turn);
  uint64_t retrieve_ally_defend_map(ARRAY_OF_BOARDS boards, uint16_t turn);
}

#endif