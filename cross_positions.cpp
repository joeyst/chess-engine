#include "position.h"
#include "masks/horizontal_masks.h"

using namespace std;
using namespace Masks;



int main () {
  auto vs = VerticalSituation(0x1000100010001, 1);
  print_board(vs.board);
  print_board(vs.flip_board_to_horizontal());
  vs.board = 0x100010001000100;
  print_board(vs.board);
  print_board(vs.flip_board_to_horizontal());
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  vs.rank = 5;
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  vs.rank = 4;
  print_board(vs.get_block_above());
  print_board(vs.get_block_below());
  print_board(vs.get_block_A_B());

  return 0;
}