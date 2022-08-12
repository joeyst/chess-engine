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

int main () {
  auto situation = Situations();
  auto situations = situation.generate_horizontal_situations();
  for (auto s : situations) {
    std::cout << "File: " << (int)s.file << endl;
    s.print_board();
  }
  cout << situations.size();

  auto vert_situations = situation.generate_vertical_situations();
  for (auto vs : vert_situations) {
    std::cout << "Rank: " << (int)vs.rank << endl;
    vs.print_board();
  }
  cout << vert_situations.size();

  return 0;
}