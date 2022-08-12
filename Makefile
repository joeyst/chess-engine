.SILENT: run

run:
	g++ -o bitmap-chess cross_positions.cpp masks/horizontal_masks.cpp position.cpp
	./bitmap-chess
	echo ""
	rm ./bitmap-chess