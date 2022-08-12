#include <cstdint>

#ifndef CROSS_POSITIONS_H
#define CROSS_POSITIONS_H
class HorizontalSituation {
  public:
    uint64_t board;
    uint8_t file;
    HorizontalSituation();
    HorizontalSituation(uint64_t b, uint8_t f);
    void print_board();
    uint64_t get_occ_to_right();
    uint64_t get_occ_to_left();
    uint64_t get_block_to_right();
    uint64_t get_block_to_left();
    uint64_t get_block_L_R();
};

class VerticalSituation {
  public:
    uint64_t board;
    uint8_t rank;
    VerticalSituation();
    VerticalSituation(uint64_t b, uint8_t r);
    void print_board();
    uint64_t get_occ_above();
    uint64_t get_occ_below();
    uint64_t get_block_above();
    uint64_t get_block_below();
    uint64_t get_block_A_B();
    uint64_t flip_board_to_horizontal();
};
#endif