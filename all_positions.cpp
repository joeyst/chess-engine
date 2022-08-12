#include "all_positions.h"
#include "cross_positions.h"
#include "position.h"
#include "masks/horizontal_masks.h"
#include "diagonal_positions.h"





using namespace std;
using namespace Masks;

vector<CrossSituation> GenerateSituations::generate_cross_situations() {
  vector<CrossSituation> cs = {};
  auto situation_object = Situations();
  for (auto hs : situation_object.generate_horizontal_situations()) {
    for (auto vs : situation_object.generate_vertical_situations()) {
      cs.push_back(CrossSituation(vs, hs));
    }
  }
  return cs;
}

unordered_map<Board, Board> GenerateSituations::get_cross_block_map() {
  unordered_map<Board, Board> cbm = {};
  for (auto cs : GenerateSituations::generate_cross_situations()) {
    cbm[cs.get_natural_board()] = cs.get_blocked_adjusted();
  }
  return cbm;
}


int main () {


  using namespace Diagonal;
  /*
  print_board(get_up_right_mask(0));
  print_board(get_up_right_mask(1));  
  print_board(get_up_right_mask(15));
  print_board(get_up_right_mask(63));
  print_board(get_up_right_mask(40));
  print_board(get_up_right_mask(23));

  cout << "DIAGONALS: " << endl;
  print_board(UP_LEFT_DIAGONAL);
  print_board(get_up_left_mask(0));
  print_board(get_up_left_mask(1));  
  print_board(get_up_left_mask(15));
  print_board(get_up_left_mask(63));
  print_board(get_up_left_mask(40));
  print_board(get_up_left_mask(23));

  cout << "SHIFTED DIAGONALS: " << endl;
  auto ss = Situations();
  ss.generate_horizontal_situations();
  for (auto k : ss.generate_horizontal_situations()) {
    cout << "Original: " << endl;
    print_board(k.board);
    print_board(Diagonal::horizontal_to_up_left(k.board));
  }
  */
  
  
  print_board(Diagonal::mask_up_right(9));
  cout << "Mask up right: " << 9;  
  print_board(Diagonal::mask_up_right(1));
  cout << "Mask up right: " << 1;  
  print_board(Diagonal::mask_up_right(42));
  cout << "Mask up right: " << 42;  
  print_board(Diagonal::mask_up_left(0));
  cout << "Mask up left: " << 0;  
  print_board(Diagonal::mask_up_left(1));
  cout << "Mask up left: " << 1;  
  print_board(Diagonal::mask_up_left(17));
  cout << "Mask up left: " << 17;  
  print_board(Diagonal::mask_up_left(63));
  cout << "Mask up left: " << 63 << endl;  
  
  cout << "Mask up left: " << 29;
  print_board(Diagonal::mask_up_left(29));
  cout << "Mask up left: " << 20;
  print_board(Diagonal::mask_up_left(20));
  cout << "Mask up left: " << 23;
  print_board(Diagonal::mask_up_left(23));
  cout << "Mask up left: " << 7;
  print_board(Diagonal::mask_up_left(7));

  auto board = EVERY_OTHER_RANK;
  print_board(board);
  cout << "get_occ_to_up_right(): " << endl;
  auto dsss = DiagonalSituation(board, 11);
  print_board(dsss.get_occ_to_up_right());
  print_board(dsss.get_occ_to_down_left());
  print_board(dsss.get_occ_to_up_left());
  print_board(dsss.get_occ_to_down_right());
  print_board(dsss.get_occ_to_direction(Diagonal::mask_up_right));

  return 0;
}