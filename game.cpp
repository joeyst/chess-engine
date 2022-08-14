#include "game.h"
#include "console.h"
#include "move_generation.h"
#include <iostream>
#include <string>
#include "constants.h"
#include <unordered_set>
#include "minimax.h"
#include "evaluation_functions.h"


using namespace Masks;
using namespace std;

ARRAY_OF_BOARDS setup_board() {
  ARRAY_OF_BOARDS state = {};
  state[WPAWN] = STARTING_WPAWNS;
  state[BPAWN] = STARTING_BPAWNS;
  state[WROOK] = STARTING_WROOKS;
  state[BROOK] = STARTING_BROOKS;
  state[WKNIGHT] = STARTING_WKNIGHTS;
  state[BKNIGHT] = STARTING_BKNIGHTS;
  state[WBISHOP] = STARTING_WBISHOPS;
  state[BBISHOP] = STARTING_BBISHOPS;
  state[WQUEEN] = STARTING_WQUEEN;
  state[BQUEEN] = STARTING_BQUEEN;  
  state[WKING] = STARTING_WKING;  
  state[BKING] = STARTING_BKING;  
  return state;
}

using namespace Boards;
using namespace GenerateMoves;




unordered_map<char, uint8_t> file_to_index = {
  {'a', 0},
  {'b', 1},
  {'c', 2},
  {'d', 3},
  {'e', 4},
  {'f', 5},
  {'g', 6},
  {'h', 7}
};

unordered_map<char, uint8_t> rank_to_index = {
  {'1', 0},
  {'2', 1},
  {'3', 2},
  {'4', 3},
  {'5', 4},
  {'6', 5},
  {'7', 6},
  {'8', 7},
};

bool valid_input(string inp) {
  if (file_to_index.count(inp[0]) == 0) return false;
  if (rank_to_index.count(inp[1]) == 0) return false;
  if (file_to_index.count(inp[2]) == 0) return false;
  if (rank_to_index.count(inp[3]) == 0) return false;
  return true;
}

Move::Move(string inp) {
  sfile = file_to_index[inp[0]];
  srank = rank_to_index[inp[1]];
  ffile = file_to_index[inp[2]];
  frank = rank_to_index[inp[3]];
}

Move::Move() {
  sfile = 0;
  srank = 0;
  ffile = 0;
  frank = 0;
}

uint8_t Move::start_square() {
  return (this->sfile + (8 * this->srank));
}

uint8_t Move::end_square() {
  return (this->ffile + (8 * this->frank));
}

Move get_input () {
  string user_input;
  cin >> user_input;
  while (valid_input(user_input) == false) {
    cout << "Invalid move, please enter again. \nE.g.: a2a7\n";
    cin >> user_input;
  }
  return Move(user_input);
}

uint8_t index_of_board_with_occupied_square(ARRAY_OF_BOARDS state, uint8_t square) {
  uint64_t value = value_from_square(square);
  for (int index = 0; index < 12; index++) {
    if (state[index] & value) return index;
  }
  return -1;
}

bool board_in_legal_states_vector(vector<ARRAY_OF_BOARDS> legal_states, ARRAY_OF_BOARDS state) {
  for (auto s : legal_states) if (s == state) return true;
  return false;
}
 
ARRAY_OF_BOARDS get_legal_input (ARRAY_OF_BOARDS state, uint16_t turn_number) {
  Move move;
  uint8_t index_of_board_with_starting_square;
  uint8_t index_of_board_with_ending_square;
  ARRAY_OF_BOARDS temp;
  vector<ARRAY_OF_BOARDS> legal_states;

  while (true) {
    if ((turn_number % 2) == 1) {
      legal_states = wstates(state);
    } else {
      legal_states = bstates(state);
    }

    move = get_input();
    index_of_board_with_starting_square = index_of_board_with_occupied_square(state, move.start_square());
    index_of_board_with_ending_square = index_of_board_with_occupied_square(state, move.end_square());

    temp = state;
    temp[index_of_board_with_ending_square] &= all_but_index(move.end_square());
    temp[index_of_board_with_starting_square] &= all_but_index(move.start_square());
    temp[index_of_board_with_starting_square] |= (value_from_square(move.end_square()));

    if (board_in_legal_states_vector(legal_states, temp)) return temp;
    print_board_with_letters(temp);
    cout << "Invalid move, please enter again. \nE.g.: a2a7\n";
  }
}

void message_for_team(uint16_t turn_number) {
  if (turn_number % 2 == 1) {
    cout << "Enter your turn, uppercase: " << endl;
  } else {
    cout << "Enter your turn, lowercase: " << endl;
  }
}

void play_game() {
  ARRAY_OF_BOARDS board = setup_board();
  uint16_t turn = 1;
  vector<ARRAY_OF_BOARDS> legal_moves;
  Move move;
  string user_input;

  while (true) {
    print_board_with_letters(board);
    message_for_team(turn);
    board = get_legal_input(board, turn);
    turn++;
  }
}

void play_engine_turn(ARRAY_OF_BOARDS &state, Minimax engine) {
  state = engine.calculate_move(wstates(state), true, engine.depth);
  print_board_with_letters(state);
  cout << "The engine has played." << endl;
  cout << "Turn: " << (int)(engine.current_turn + 1) << endl;
}

void play_player_turn(uint16_t current_turn, ARRAY_OF_BOARDS &state) {
  state = get_legal_input(state, current_turn);
  print_board_with_letters(state);
}

void play_with_engine(uint8_t depth, int16_t (*eval) (ARRAY_OF_BOARDS)) {
  auto board = setup_board();
  Minimax engine;
  uint16_t turn = 0;

  while (true) {
    turn++;
    engine = Minimax(depth, eval, turn);
    play_engine_turn(board, engine);
    turn++;
    play_player_turn(turn, board);
  }

}

int main () {
  play_with_engine(3, EvaluationFunction::simple_count_of_points);
  return 0;
}