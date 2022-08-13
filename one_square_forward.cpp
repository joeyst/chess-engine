#include "one_square_forward.h"
#include <vector>
#include <iostream>

using namespace std;
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


uint64_t SquareMoves::calculate_square_moves(uint64_t square) {
  int16_t signed_square = square;
  vector<int16_t> offets = {9, 8, 7, 1, -1, -7, -8, -9};
  vector<int16_t> new_squares = {};
  for (auto o : offets) {
    if (((signed_square + o) >= 0) && ((signed_square + o) <= 63)) new_squares.push_back(signed_square + o);
  }

  int16_t file = (square % 8);
  int16_t rank = (square / 8);

  int16_t temp_file;
  int16_t temp_rank;

  int16_t file_dif;
  int16_t rank_dif;

  vector<uint16_t> legal_squares = {};
  for (auto sqr : new_squares) {
    temp_file = (sqr % 8);
    temp_rank = (sqr / 8);
    
    file_dif = (temp_file - file);
    rank_dif = (temp_rank - rank);

    if (file_dif < 0) file_dif *= -1;
    if (rank_dif < 0) rank_dif *= -1;

    if ((file_dif <= 1) && (rank_dif <= 1)) legal_squares.push_back(sqr);
  }

  uint64_t new_board = 0;
  for (auto sqr : legal_squares) new_board |= value_from_square(sqr);
  return new_board;
}