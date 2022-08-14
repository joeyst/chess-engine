#include "include_files.h"
#include "constants.h"
#include "board.h"
#include "minimax.h"

#ifndef GAME_H
#define GAME_H

ARRAY_OF_BOARDS setup_board();
extern unordered_map<char, uint8_t> file_to_index;
extern unordered_map<char, uint8_t> rank_to_index;
bool valid_input(string inp);

void play_game();
class Move {
  public: 
    uint8_t sfile;
    uint8_t srank;
    uint8_t ffile;
    uint8_t frank;
    Move(string inp);
    Move();
    uint8_t start_square();
    uint8_t end_square();
};
Move get_input();

void play_engine_turn(std::ARRAY_OF_BOARDS &state, Minimax engine);
void play_with_engine(uint8_t depth, int16_t (*eval) (ARRAY_OF_BOARDS));
void play_player_turn(uint16_t current_turn, std::ARRAY_OF_BOARDS &state);

#endif