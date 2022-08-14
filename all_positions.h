#include "cross_positions.h"
#include <unordered_map>
#include "diagonal_positions.h"





#ifndef ALL_POSITIONS_H
#define ALL_POSITIONS_H

typedef uint64_t Board;

class GenerateSituations {
  public:
    static vector<CrossSituation> generate_cross_situations();
    static unordered_map<Board, Board> get_cross_block_map();
    static unordered_map<uint8_t, unordered_map<Board, Board>> get_cross_block_map_map(); 
    
};

#endif