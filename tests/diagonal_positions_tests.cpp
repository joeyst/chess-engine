#include <cassert>
#include "../diagonal_positions.h"
#include "diagonal_positions_tests.h"
#include <iostream>
#include "../masks/horizontal_masks.h"
#include <string>
#include <cstring>
#include "../constants.h"

using namespace std;
using namespace Masks;
using namespace Diagonal;

void diagonal_positions_tests() {
  assert(get_up_right_mask(10) == 36099303471055874);
  assert(get_up_right_mask(45) == UP_RIGHT_DIAGONAL);

  assert((get_up_left_mask(10)) == 0x1020408);
  assert((get_up_left_mask(45)) == 580999813328273408);

  assert((mask_up_right(10)) == (0x80402010080000));
  assert((mask_up_left(10)) == (0x01020000));
  assert((mask_down_right(10)) == (0x08));
  assert((mask_down_left(10)) == (0x02));

  auto ds = DiagonalSituation(UP_RIGHT_DIAGONAL, 9);
  assert(ds.get_blocked_to_up_right() == 0x8040201008000000); 

  ds = DiagonalSituation(EVERY_OTHER_RANK, 29);
  assert(ds.get_blocked_to_up_left() == 0x204080000000000);

  assert(isolate_msb(0) == 0);
  assert(isolate_msb(18) == 16);
  assert(isolate_msb(16) == 16);

  assert(ds.get_blocked_to_down_right() == 0x8000);
  assert(ds.get_blocked_to_down_left() == 0x804);

  assert(ds.get_blocked_in_all_diagonals() == 0x0204880000008804);
  ds.square = 34;
  assert(ds.get_blocked_in_all_diagonals() == 0x2000000000002040);

  assert(mask_to_all_diag_excluding_own_square(35) == 0x4122140014224180);
  assert(mask_to_all_diag_excluding_own_square(0) == 0x8040201008040200);
  assert(mask_to_all_diag_excluding_own_square(63) == 0x40201008040201);
  assert(mask_to_all_diag_excluding_own_square(56) == 0x2040810204080);
  
}