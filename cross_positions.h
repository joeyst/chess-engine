#include <cstdint>
#include <vector>
#include "position.h"

#ifndef CROSS_POSITIONS_H
#define CROSS_POSITIONS_H
using namespace std;

class CrossSituation {
  public:
    VerticalSituation vs;
    HorizontalSituation hs;
    CrossSituation(VerticalSituation vert_s, HorizontalSituation horiz_s);
    uint8_t get_file();
    uint8_t get_rank();
    uint64_t get_adjusted_horizontal();
    uint64_t get_adjusted_vertical();
    uint64_t get_natural_board();
    uint8_t get_square();
};

class Situations {
  public:
    vector<HorizontalSituation> horizontal_situations;
    vector<VerticalSituation> vertical_situations;
    Situations();
    vector<HorizontalSituation> generate_horizontal_situations_for_file(int file);
    vector<HorizontalSituation> generate_horizontal_situations();
    vector<VerticalSituation> generate_vertical_situations_for_rank(int rank);
    vector<VerticalSituation> generate_vertical_situations();
};

#endif