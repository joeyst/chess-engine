#include <cstdint>
#include <vector>
#include "position.h"

#ifndef CROSS_POSITIONS_H
#define CROSS_POSITIONS_H
using namespace std;

class Situations {
  public:
    vector<HorizontalSituation> horizontal_situations;
    vector<VerticalSituation> vertical_situations;
    Situations();
    vector<HorizontalSituation> generate_horizontal_situations_for_file(int file);
    vector<HorizontalSituation> generate_horizontal_situations();
};

#endif