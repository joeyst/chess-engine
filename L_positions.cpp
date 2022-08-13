#include "L_positions.h"
#include "constants.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace L_shape;

uint64_t L_shape::generate_L_from_square(uint8_t square) {
  int8_t temp_signed = square;
  vector<signed int8_t> offset = {-15, -17, -10, -6, 6, 10, 15, 17};
  vector<uint8_t> squares = {};
  for (auto o : offset) {
    if (((temp_signed + o) >= 0) && ((temp_signed + o) <= 63) )squares.push_back(temp_signed + o);
  }

  int16_t file = (square % 8);
  int16_t rank = (square / 8);

  int16_t temp_file;
  int16_t temp_rank;

  int16_t dif_in_file;
  int16_t dif_in_rank;
  vector<uint8_t> new_squares = {};
  for (auto s : squares) {
    temp_file = (s % 8);
    temp_rank = (s / 8);

    dif_in_file = temp_file - file;
    dif_in_rank = temp_rank - rank;

    if (dif_in_file < 0) dif_in_file *= -1;
    if (dif_in_rank < 0) dif_in_rank *= -1;

    if (dif_in_file <= 2 && dif_in_rank <= 2) new_squares.push_back(s);
  }

  uint64_t new_board = 0;
  for (auto sq : new_squares) new_board |= value_from_square(sq);
  return new_board;
}