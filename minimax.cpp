#include "minimax.h"
#include "constants.h"
#include <vector>
#include <array>
#include "move_generation.h"
#include "console.h"
#include "evaluation_functions.h"
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace GenerateMoves;

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

int16_t Minimax::evaluate_position(ARRAY_OF_BOARDS choice) {
  return this->eval_function(choice);
}

int16_t Minimax::grab_max_value(vector<ARRAY_OF_BOARDS> choices) {
  int16_t max_value = -100;
  for (auto choice : choices) if (this->evaluate_position(choice) > max_value) max_value = this->evaluate_position(choice);
  return max_value;
}

int16_t Minimax::grab_min_value(vector<ARRAY_OF_BOARDS> choices) {
  int16_t min_value = 100;
  for (auto choice : choices) if (this->evaluate_position(choice) < min_value) min_value = this->evaluate_position(choice);
  return min_value;
}

int16_t Minimax::evaluate_position_recursive(vector<ARRAY_OF_BOARDS> choices, bool maximize, uint8_t depth_left) {
  if (depth_left == 0) return this->grab_max_value(choices);

  vector<int16_t> possible_values;
  if (maximize) {
    for (auto choice : choices) possible_values.push_back(evaluate_position_recursive(bstates(choice), false, depth_left - 1));
    return *max_element(possible_values.begin(), possible_values.end());
  } 
  
  else {
    for (auto choice : choices) possible_values.push_back(evaluate_position_recursive(wstates(choice), true, depth_left - 1));
    return *min_element(possible_values.begin(), possible_values.end());
  }
}

ARRAY_OF_BOARDS Minimax::collect_values_and_pick_best_move(vector<ARRAY_OF_BOARDS> choices, bool maximize = true, uint8_t depth_left = 0) {
  int16_t max_value = -100;
  ARRAY_OF_BOARDS desired_choice;
  for (auto choice : choices) if (evaluate_position_recursive({choice}) > max_value) {
    max_value = evaluate_position_recursive({choice});
    desired_choice = choice;
  }
  return desired_choice;
}

ARRAY_OF_BOARDS Minimax::calculate_move(vector<ARRAY_OF_BOARDS> choices, bool maximize = true, uint8_t depth_left = 0) {
  return this->collect_values_and_pick_best_move(choices, maximize, depth_left); 
}