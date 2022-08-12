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
  auto situation = Situations();
  auto situations = situation.generate_horizontal_situations();
  for (auto s : situations) {
    //std::cout << "File: " << (int)s.file << endl;
    //s.print_board();
  }
  //cout << situations.size();

  auto vert_situations = situation.generate_vertical_situations();
  for (auto vs : vert_situations) {
    //std::cout << "Rank: " << (int)vs.rank << endl;
    //vs.print_board();
  }
  //cout << vert_situations.size();

  auto vss = VerticalSituation(0x01010101, 5);
  auto hss = HorizontalSituation(0xFE, 0);
  auto css = CrossSituation(vss, hss);

  //print_board(css.get_natural_board());
  //print_board(css.get_horiz_blocked_adjusted());
  //print_board(css.get_vert_blocked_adjusted());
  //print_board(css.get_blocked_adjusted());

  // auto all_cross_situations = GenerateSituations::generate_cross_situations();
  // for (auto i : all_cross_situations) print_board(i.get_natural_board());
  /*
  auto gcs = GenerateSituations::generate_cross_situations();
  for (int i = 0; i < gcs.size() / 200; i++) {
    print_board((gcs[i * 10]).get_natural_board());
  }
  */




  auto cbm = GenerateSituations::get_cross_block_map();
  /*
  for (auto kv : cbm) {
    cout << "Position: " << endl;
    print_board(kv.first);
    cout << "Blockage: " << endl;
    print_board(kv.second);
  }
  */

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

  return 0;
}