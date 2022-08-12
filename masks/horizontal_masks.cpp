#include "horizontal_masks.h"

uint64_t Masks::mask_to_left(int file) {
  return (FIRST_HORIZONTAL >> (8 - file));
}

uint64_t Masks::mask_to_right(int file) {
  auto a = FIRST_HORIZONTAL;
  a <<= (file + 1);
  return (a & FIRST_HORIZONTAL);
}