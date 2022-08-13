.SILENT: run

run:
	g++ -o bitmap-chess cross_positions.cpp masks/horizontal_masks.cpp position.cpp all_positions.cpp diagonal_positions.cpp mask.cpp constants.cpp tests/diagonal_positions_tests.cpp L_positions.cpp
	./bitmap-chess
	echo ""
	rm ./bitmap-chess