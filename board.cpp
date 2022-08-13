#include "board.h"
#include "move_generation.h"



using namespace Boards;
uint64_t Boards::retrieve_occ_in_range(array<uint64_t, 12> boards, uint8_t lower, uint8_t upper_inclusive) {
  uint64_t all_occ = 0;
  for (int t = lower; t <= upper_inclusive; t++) all_occ |= boards[t];

  uint64_t duplication_check = 0;
  for (int t = lower; t <= upper_inclusive; t++) duplication_check ^= boards[t];

  assert(all_occ == duplication_check);
  return all_occ;
}

uint64_t Boards::retrieve_all_occ(array<uint64_t, 12> boards) {
  return retrieve_occ_in_range(boards, 0, 11);
}

uint64_t Boards::retrieve_white_occ(array<uint64_t, 12> boards) {
  return retrieve_occ_in_range(boards, 0, 5);
}

uint64_t Boards::retrieve_black_occ(array<uint64_t, 12> boards) {
  return retrieve_occ_in_range(boards, 6, 11);
}

uint64_t Boards::retrieve_ally_occ(array<uint64_t, 12> boards, uint16_t turn) {
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

uint64_t Boards::retrieve_enemy_occ(array<uint64_t, 12> boards, uint16_t turn) {
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


vector<uint64_t> Boards::generate_wboard_states(array<uint64_t, 12> boards) {
  vector<uint64_t> states = {};
  
  return states;
}

vector<uint64_t> Boards::generate_bboard_states(array<uint64_t, 12> boards) {
  vector<uint64_t> states = {};

  return states;
}

vector<uint64_t> Boards::generate_board_states(array<uint64_t, 12> boards, uint16_t turn) {
  if (turn % 2 == 1) {
    return generate_wboard_states(boards);
  } else {
    return generate_bboard_states(boards);
  }
}


int main () {
  using namespace Diagonal;
  diagonal_positions_tests();
  array<uint64_t, 12> board = {};
  board[WPAWN] = 0xFEF0FF00;
  board[BPAWN] = 0x0200000000;
  for (auto a : GenerateMoves::Pawn::generate_wpawn_states(board)) Masks::print_board(a[3]);
  return 0;
}