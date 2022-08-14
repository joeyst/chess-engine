#include <cstdint>
#include <array>

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ARRAY_OF_BOARDS array<uint64_t, 12>

#define WHOLE_BOARD 0xFFFFFFFFFFFFFFFF

#define ALL_BUT_FIRST_VERTICAL 0xFEFEFEFEFEFEFEFE
#define ALL_BUT_LAST_VERTICAL 0x7F7F7F7F7F7F7F7F
#define FIRST_VERTICAL 0x0101010101010101

#define FIRST_HORIZONTAL 0xFF
#define TOP_SQUARE_OF_VERTICAL 0x0100000000000000
#define LAST_SQUARE_OF_HORIZONTAL 0x80

#define UP_RIGHT_DIAGONAL 0x8040201008040201
#define UP_LEFT_DIAGONAL 0x0102040810204080

#define EVERY_OTHER_RANK 0xFF00FF00FF00FF
#define EVERY_OTHER_FILE 0x5555555555555555

#define TEST_DIAGONAL_IN_TOP_LEFT_QUADRANT 0x402010000000000
#define TEST_DIAGONAL_IN_TOP_RIGHT_QUADRANT 0x2040800000000000
#define TEST_DIAGONAL_IN_BOTTOM_RIGHT_QUADRANT 0x804020
#define TEST_DIAGONAL_IN_BOTTOM_LEFT_QUADRANT 0x10204

#define SECOND_HORIZONTAL_FROM_TOP 0xFF000000000000
#define SECOND_HORIZONTAL_FROM_BOTTOM 0xFF00

#define WHITE 0
#define BLACK 7

#define OFFSET_HEX_7_RANKS 00000000000000
#define STARTING_WPAWNS 0xFF00
#define STARTING_BPAWNS 0xFF000000000000
#define STARTING_WROOKS 0x81
#define STARTING_BROOKS 0x8100000000000000
#define STARTING_WKNIGHTS 0x42
#define STARTING_BKNIGHTS 0x4200000000000000
#define STARTING_WBISHOPS 0x24
#define STARTING_BBISHOPS 0x2400000000000000
#define STARTING_WQUEEN 0x8
#define STARTING_BQUEEN 0x800000000000000
#define STARTING_WKING 0x10
#define STARTING_BKING 0x1000000000000000

#define ALL_BUT_FIRST_HORIZONTAL 0xFFFFFFFFFFFFFF00
#define ALL_BUT_LAST_HORIZONTAL 0xFFFFFFFFFFFFFF



uint64_t isolate_lsb(uint64_t board);
uint64_t isolate_msb(uint64_t board);

uint64_t value_from_square(uint8_t square);
uint64_t all_but_index(uint8_t square);

uint8_t count_pieces_on_slice(uint64_t board);

std::array<uint8_t, 12> piece_count(std::ARRAY_OF_BOARDS state);

namespace Masks {
  uint64_t mask_of_given_rank(uint8_t rank);
  uint64_t mask_of_given_file(uint8_t file);
  uint64_t mask_to_left_of_square(uint8_t square);
  uint64_t mask_to_right_of_square(uint8_t square);
  uint64_t mask_above_of_square(uint8_t square);
  uint64_t mask_below_of_square(uint8_t square);
  uint64_t mask_of_cross_outside_of_square(uint8_t square);
}

#endif