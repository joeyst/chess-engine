#include "minimax.h"
#include "constants.h"
#include <vector>
#include <array>
#include "move_generation.h"
#include "console.h"

using namespace std;
using namespace GenerateMoves;

namespace EvaluationFunction {

  namespace {
    array<int16_t, 12> points_per_piece{5, 3, 9, 1, 3, 100, -5, -3, -9, -1, -3, -100};
  }

  int16_t simple_count_of_points(ARRAY_OF_BOARDS state) {
    array<uint8_t, 12> count = piece_count(state);
    int16_t points = 0;
    int16_t current_points;

    for (int slice_index = 0; slice_index < 12; slice_index++) {
      current_points = count_pieces_on_slice(state[slice_index]);
      points += (current_points * points_per_piece[slice_index]);
    }
    return points;
  }

}


Minimax::Minimax(uint8_t d, int16_t (*eval) (ARRAY_OF_BOARDS), uint16_t turn) : depth(d), eval_function(eval), current_turn(turn){}
Minimax::Minimax() : depth(0), eval_function(EvaluationFunction::simple_count_of_points), current_turn(0) {}

ARRAY_OF_BOARDS Minimax::grab_trait(vector<ARRAY_OF_BOARDS> choices, function<bool(uint8_t, uint8_t)> comparison_operator) {
  ARRAY_OF_BOARDS most_desired = choices[0];
  uint8_t best_eval = this->eval_function(choices[0]);

  for (auto choice : choices) if (comparison_operator(this->eval_function(choice), best_eval)) {
    most_desired = choice;
    best_eval = this->eval_function(choice);
  }
  return most_desired;
}

ARRAY_OF_BOARDS Minimax::grab_max(vector<ARRAY_OF_BOARDS> choices) {
  return this->grab_trait(choices, greater<uint8_t>());
}

ARRAY_OF_BOARDS Minimax::grab_min(vector<ARRAY_OF_BOARDS> choices) {
  return this->grab_trait(choices, less<uint8_t>());
}

ARRAY_OF_BOARDS Minimax::calculate_move(vector<ARRAY_OF_BOARDS> choices, bool maximize = true, uint8_t depth_left = 0) {
  if (depth_left == 0) return this->grab_max(choices);
  vector<ARRAY_OF_BOARDS> candidates;

  if (maximize) {
    for (auto choice : choices) candidates.push_back(calculate_move(bstates(choice), false, depth_left - 1));
    return this->grab_max(candidates);
  } 
  
  else {
    for (auto choice : choices) candidates.push_back(calculate_move(wstates(choice), true, depth_left - 1));
    return this->grab_min(candidates);
  }
}