#include <cstdint>

#ifndef CROSS_POSITIONS_H
#define CROSS_POSITIONS_H
class HorizontalSituation {
  public:
    uint64_t board;
    uint8_t file;
    HorizontalSituation();
    HorizontalSituation(uint64_t b, uint8_t f);
};
#endif