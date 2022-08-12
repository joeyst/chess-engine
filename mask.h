#include <cstdint>
#include "constants.h"

#ifndef MASK_H
#define MASK_H

namespace Mask {
  uint64_t fill_to_right(uint8_t file);
  uint64_t fill_to_left(uint8_t file);
}
#endif