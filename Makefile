.SILENT: run

run:
	g++ -o bitmap-chess cross_positions.cpp
	./bitmap-chess
	echo ""
	rm ./bitmap-chess