#include <array> 
#include <vector>
#include "constants.h"
#include <map>
#include <functional>
#include <cstdint>

#ifndef MINIMAX_H
#define MINIMAX_H

class Minimax {

  int16_t (*eval_function) (std::ARRAY_OF_BOARDS);
  
  inline std::ARRAY_OF_BOARDS grab_trait(std::vector<std::ARRAY_OF_BOARDS> choices, std::function<bool(uint8_t, uint8_t)> comparison_operator);
  inline std::ARRAY_OF_BOARDS grab_max(std::vector<std::ARRAY_OF_BOARDS>);
  inline std::ARRAY_OF_BOARDS grab_min(std::vector<std::ARRAY_OF_BOARDS>);
  inline int16_t grab_max_value(std::vector<std::ARRAY_OF_BOARDS> choices);
  inline int16_t grab_min_value(std::vector<std::ARRAY_OF_BOARDS> choices);
  

  public: 
    Minimax(uint8_t d, int16_t (*eval) (std::ARRAY_OF_BOARDS), uint16_t turn);
    int16_t evaluate_position(std::ARRAY_OF_BOARDS choice);
    int16_t evaluate_position_recursive(std::vector<std::ARRAY_OF_BOARDS> choices, bool maximize = 1, uint8_t depth_left = 0);
    std::ARRAY_OF_BOARDS collect_values_and_pick_best_move(std::vector<std::ARRAY_OF_BOARDS> choices, bool maximize, uint8_t depth_left);
    std::ARRAY_OF_BOARDS calculate_move(std::vector<std::ARRAY_OF_BOARDS> choices, bool maximize, uint8_t depth_left);
    Minimax();
    uint8_t depth;
    uint16_t current_turn;
};

#endif