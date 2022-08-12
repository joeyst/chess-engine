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
  
}