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

  //auto all_cross_situations = GenerateSituations::generate_cross_situations();
  //for (auto i : all_cross_situations) print_board(i.get_natural_board());

  return 0;
}