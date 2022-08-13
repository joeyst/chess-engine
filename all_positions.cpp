#include "all_positions.h"
#include "cross_positions.h"
#include "position.h"
#include "masks/horizontal_masks.h"
#include "diagonal_positions.h"
#include <cassert>
#include "tests/diagonal_positions_tests.h"
#include "constants.h"
#include "L_positions.h"
#include "one_square_forward.h"





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
  diagonal_positions_tests();
  
  uint64_t starting_pawns = 0xFF10;
  print_board(TwoSqrs::calculate_moves_two_up(starting_pawns, 0));
  print_board(TwoSqrs::calculate_moves_two_down(starting_pawns + 0x0F000000000000, 0));
  print_board(TwoSqrs::calculate_moves_two_up(starting_pawns, EVERY_OTHER_FILE));
  print_board(EVERY_OTHER_FILE);
  uint64_t b = 0xF0000;
  print_board(TwoSqrs::calculate_moves_two_up(starting_pawns, b));
  print_board(OneSqr::calculate_moves_one_up(starting_pawns, b));
  print_board(ForwardAndToSide::calculate_moves_right_and_up(starting_pawns, starting_pawns));
  print_board(ForwardAndToSide::calculate_moves_left_and_up(starting_pawns, starting_pawns));


  return 0;
}