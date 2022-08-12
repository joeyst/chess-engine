#include <cstdint>

#ifndef HORIZONTAL_MASKS_H
#define HORIZONTAL_MASKS_H
#define FIRST_HORIZONTAL 0xFF

namespace Masks {
  uint64_t mask_to_left(int file);
  uint64_t mask_to_right(int file);
}
#endif