#include <cstdint>
#include "constants.h"
#include "mask.h"

#ifndef DIAGONAL_POSITIONS_H
#define DIAGONAL_POSITIONS_H

class DiagonalSituation {
  public: 
    uint64_t board;
    uint8_t square;
    DiagonalSituation(uint64_t b, uint8_t s);
    uint8_t get_up_left_diagonal_number();
    uint8_t get_up_right_diagonal_number();
    uint8_t get_file();
    uint8_t get_rank();
    uint64_t get_occ_to_direction(uint64_t (*mask_of_square) (uint8_t));
    uint64_t get_occ_to_up_right();
    uint64_t get_occ_to_up_left();
    uint64_t get_occ_to_down_right();
    uint64_t get_occ_to_down_left();
};

namespace Diagonal {
signed int get_up_right_diagonal_number(uint8_t square);
signed int get_up_left_diagonal_number(uint8_t square);

uint64_t get_up_right_mask(uint8_t square);
uint64_t get_up_left_mask(uint8_t square);

uint64_t horizontal_to_up_right(uint64_t board);
uint64_t horizontal_to_up_left(uint64_t board);

uint64_t generate_up_right_situations();
uint64_t generate_up_left_situations();

uint64_t normalize_up_right(uint64_t board, uint8_t square);
uint64_t normalize_up_left(uint64_t board, uint8_t square);

uint64_t mask_to_direction(uint64_t (*diag) (uint8_t), uint64_t (*fill_direction) (uint8_t), uint8_t square);
uint64_t mask_up_right(uint8_t square);
uint64_t mask_down_right(uint8_t square);
uint64_t mask_up_left(uint8_t square);
uint64_t mask_down_left(uint8_t square);
}

class UpRightDiagonalPosition {};

#endif