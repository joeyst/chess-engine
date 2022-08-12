#include <cstdint>
#include <iostream>
#include <vector>

#ifndef HORIZONTAL_MASKS_H
#define HORIZONTAL_MASKS_H
#define FIRST_HORIZONTAL 0xFF
#define FIRST_VERTICAL 0x0101010101010101

using namespace std;
namespace Masks {
  uint64_t mask_to_left(int file);
  uint64_t mask_to_right(int file);
  uint64_t mask_above(int rank);
  uint64_t mask_below(int rank);
  void print_board(uint64_t board);
}
#endif