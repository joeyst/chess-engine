#include "position.h"
#include "masks/horizontal_masks.h"
#include "cross_positions.h"

using namespace std;
using namespace Masks;

Situations::Situations() : horizontal_situations({}), vertical_situations({}){}

vector<HorizontalSituation> Situations::generate_horizontal_situations_for_file(int file) {
  vector<HorizontalSituation> hs = {};
  int pos;
  int file_value = (1 << file);

  for (int permutation = 0; permutation < 64; permutation++) {
    pos = (permutation << 1);
    if (!(file_value & pos)) hs.push_back(HorizontalSituation(pos, file));
  }
  return hs;
}

vector<HorizontalSituation> Situations::generate_horizontal_situations() {
  vector<HorizontalSituation> hs = {};
  for (int file = 0; file < 8; file++) {
    for (auto situation : generate_horizontal_situations_for_file(file)) hs.push_back(situation);
  }
  return hs;
}

vector<VerticalSituation> Situations::generate_vertical_situations() {
  vector<VerticalSituation> vs = {};
  for (auto situation : Situations::generate_horizontal_situations()) {
    vs.push_back(VerticalSituation(FlipBoard::flip_board_to_vertical(situation.board), situation.file));
  }
  return vs;
}

CrossSituation::CrossSituation(VerticalSituation vert_s, HorizontalSituation horiz_s) : vs(vert_s), hs(horiz_s){}

uint8_t CrossSituation::get_file() {
  return this->hs.file;
}

uint8_t CrossSituation::get_rank() {
  return this->vs.rank;
}

uint64_t CrossSituation::get_adjusted_horizontal() {
  return ((this->hs.board) << ((this->get_rank()) * 8));
}

uint64_t CrossSituation::get_adjusted_vertical() {
  return ((this->vs.board) << (this->get_file()));
}

uint64_t CrossSituation::get_natural_board() {
  return ((this->get_adjusted_horizontal()) | (this->get_adjusted_vertical()));
}

uint64_t CrossSituation::get_horiz_blocked_adjusted() {
  return ((hs.get_block_L_R()) << (8 * this->get_rank()));
}

uint64_t CrossSituation::get_vert_blocked_adjusted() {
  return ((vs.get_block_A_B()) << (this->get_file()));
}

uint64_t CrossSituation::get_blocked_adjusted() {
  return ((this->get_horiz_blocked_adjusted()) | (this->get_vert_blocked_adjusted()));
}