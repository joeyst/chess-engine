#include "board.h"


const unordered_map<Board, Board> cross_block_map = GenerateSituations::get_cross_block_map();
unordered_map<Board, Board> diag_block_map = {};

uint64_t retrieve_occ_in_range(uint64_t boards[12], uint8_t lower, uint8_t upper_inclusive) {
  uint64_t all_occ = 0;
  for (int t = lower; t <= upper_inclusive; t++) all_occ |= boards[t];

  uint64_t duplication_check = 0;
  for (int t = lower; t < upper_inclusive; t++) duplication_check ^= boards[t];

  assert(all_occ == duplication_check);
  return all_occ;
}

uint64_t retrieve_all_occ(uint64_t boards[12]) {
  return retrieve_occ_in_range(boards, 0, 11);
}

uint64_t retrieve_white_occ(uint64_t boards[12]) {
  return retrieve_occ_in_range(boards, 0, 5);
}

uint64_t retrieve_black_occ(uint64_t boards[12]) {
  return retrieve_occ_in_range(boards, 6, 11);
}

uint64_t retrieve_ally_occ(uint64_t boards[12], uint16_t turn) {
  if (turn % 2 == 1) {
    return retrieve_white_occ(boards);
  } 
  else if (turn % 2 == 0) {
    return retrieve_black_occ(boards);
  }
  else {
    throw logic_error("Turn is neither even nor odd.");
  }
}

uint64_t retrieve_enemy_occ(uint64_t boards[12], uint16_t turn) {
  if (turn % 2 == 1) {
    return retrieve_black_occ(boards);
  }
  else if (turn % 2 == 0) {
    return retrieve_white_occ(boards);
  }
  else {
    throw logic_error("Turn is neither even nor odd.");
  }
}



int main () {
  using namespace Diagonal;
  diagonal_positions_tests();
  return 0;
}