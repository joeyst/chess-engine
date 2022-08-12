.SILENT: run

run:
	g++ -o bitmap-chess cross_positions.cpp masks/horizontal_masks.cpp
	./bitmap-chess
	echo ""
	rm ./bitmap-chess