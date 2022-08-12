#include <cstdint>

#ifndef DIAGONAL_POSITIONS_H
#define DIAGONAL_POSITIONS_H

#define UP_RIGHT_DIAGONAL 0x8040201008040201
#define UP_LEFT_DIAGONAL 0x0102040810204080

#define ALL_BUT_FIRST_VERTICAL 0xFEFEFEFEFEFEFEFE
#define ALL_BUT_LAST_VERTICAL 0x7F7F7F7F7F7F7F7F

namespace Diagonal {
uint64_t get_up_right_mask(uint8_t square);
uint64_t get_up_left_mask(uint8_t square);

uint64_t horizontal_to_up_right(uint64_t board);
uint64_t horizontal_to_up_left(uint64_t board);
}

class UpRightDiagonalPosition {};

#endif