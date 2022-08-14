#include <array> 
#include <vector>
#include "constants.h"
#include <map>
#include <functional>

#ifndef MINIMAX_H
#define MINIMAX_H

class Minimax {

  int16_t (*eval_function) (std::ARRAY_OF_BOARDS);
  
  inline std::ARRAY_OF_BOARDS grab_trait(std::vector<std::ARRAY_OF_BOARDS> choices, std::function<bool(uint8_t, uint8_t)> comparison_operator);
  inline std::ARRAY_OF_BOARDS grab_max(std::vector<std::ARRAY_OF_BOARDS>);
  inline std::ARRAY_OF_BOARDS grab_min(std::vector<std::ARRAY_OF_BOARDS>);

  public: 
    Minimax(uint8_t d, int16_t (*eval) (std::ARRAY_OF_BOARDS), uint16_t turn);
    std::ARRAY_OF_BOARDS calculate_move(std::vector<std::ARRAY_OF_BOARDS> choices, bool maximize, uint8_t depth_left);
    Minimax();
    uint8_t depth;
    uint16_t current_turn;

};

namespace EvaluationFunction {

  namespace {
    extern std::array<int16_t, 12> points_per_piece;
  }

  int16_t simple_count_of_points(std::ARRAY_OF_BOARDS state);

}

#endif