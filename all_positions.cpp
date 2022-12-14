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



unordered_map<Board, Board> cross_block_map = GenerateSituations::get_cross_block_map();
unordered_map<uint8_t, unordered_map<Board, Board>> cross_block_map_map = GenerateSituations::get_cross_block_map_map();
unordered_map<Board, Board> diag_block_map = {};
unordered_map<uint8_t, unordered_map<Board, Board>> diag_block_map_map = {};

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


unordered_map<uint8_t, unordered_map<Board, Board>> GenerateSituations::get_cross_block_map_map() {
  unordered_map<uint8_t, unordered_map<Board, Board>> map_of_maps = {};
  for (auto cs : generate_cross_situations()) {
    map_of_maps[cs.get_square()][cs.get_natural_board()] = cs.get_blocked_adjusted();
  }
  return map_of_maps;
}
