.SILENT: run

run:
	g++ -o bitmap-chess cross_positions.cpp masks/horizontal_masks.cpp position.cpp all_positions.cpp diagonal_positions.cpp mask.cpp constants.cpp tests/diagonal_positions_tests.cpp L_positions.cpp one_square_forward.cpp board.cpp move_generation.cpp pawn_move_generation.cpp move_generation_utility.cpp knight_move_generation.cpp rook_move_generation.cpp bishop_move_generation.cpp queen_move_generation.cpp king_move_generation.cpp
	./bitmap-chess
	echo ""
	rm ./bitmap-chess