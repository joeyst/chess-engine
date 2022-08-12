#include "cross_positions.h"
#include <unordered_map>





#ifndef ALL_POSITIONS_H
#define ALL_POSITIONS_H

typedef uint64_t Board;

class GenerateSituations {
  public:
    static vector<CrossSituation> generate_cross_situations();
    static unordered_map<Board, Board> get_cross_block_map();
    const unordered_map<Board, Board> cross_block_map = GenerateSituations::get_cross_block_map();

    
};

#endif