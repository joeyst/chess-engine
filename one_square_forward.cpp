#include "one_square_forward.h"

using namespace OneSqr;
uint64_t OneSqr::generate_one_square_up(uint64_t board) {
  return (board << 8);
}

uint64_t OneSqr::generate_one_square_down(uint64_t board) {
  return (board >> 8);
}

uint64_t OneSqr::calculate_moves_one_forward(uint64_t starting_pawns, uint64_t board, uint64_t (*transform) (uint64_t)) {
  auto moved = transform(starting_pawns);
  auto occ = (moved & board);
  return (moved ^ occ);
}

uint64_t OneSqr::calculate_moves_one_up(uint64_t starting_pawns, uint64_t board) {
  return calculate_moves_one_forward(starting_pawns, board, generate_one_square_up);
}

uint64_t OneSqr::calculate_moves_one_down(uint64_t starting_pawns, uint64_t board) {
  return calculate_moves_one_forward(starting_pawns, board, generate_one_square_down);
}


uint64_t TwoSqrs::calculate_moves_two_up(uint64_t starting_pawns, uint64_t board) {
  starting_pawns &= SECOND_HORIZONTAL_FROM_BOTTOM;
  auto one_forward = calculate_moves_one_up(starting_pawns, board);
  return calculate_moves_one_up(one_forward, board);
}

uint64_t TwoSqrs::calculate_moves_two_down(uint64_t starting_pawns, uint64_t board) {
  starting_pawns &= SECOND_HORIZONTAL_FROM_TOP;
  auto one_forward = calculate_moves_one_down(starting_pawns, board);
  return calculate_moves_one_down(one_forward, board);
}

uint64_t ForwardAndToSide::calculate_moves_right_and_up(uint64_t starting_pawns, uint64_t enemies) {
  starting_pawns &= ALL_BUT_LAST_VERTICAL;
  uint64_t potential_moves = (starting_pawns << 9);
  return (potential_moves & enemies);
}

uint64_t ForwardAndToSide::calculate_moves_right_and_down(uint64_t starting_pawns, uint64_t enemies) {
  starting_pawns &= ALL_BUT_LAST_VERTICAL;
  uint64_t potential_moves = (starting_pawns >> 7);
  return (potential_moves & enemies);
}

uint64_t ForwardAndToSide::calculate_moves_left_and_up(uint64_t starting_pawns, uint64_t enemies) {
  starting_pawns &= ALL_BUT_FIRST_VERTICAL;
  uint64_t potential_moves = (starting_pawns << 7);
  return (potential_moves & enemies);
}

uint64_t ForwardAndToSide::calculate_moves_left_and_down(uint64_t starting_pawns, uint64_t enemies) {
  starting_pawns &= ALL_BUT_FIRST_VERTICAL;
  uint64_t potential_moves = (starting_pawns >> 9);
  return (potential_moves & enemies);
}