#pragma once
#include "Map.h"

// only the generate function is called by Map - other functions exposed for testing
namespace MapGenerator {
	grid generateUnconnectedGrid(int w, int h);
	tile findTileWithValue(grid g, int v);
	void floodFill(grid &g, tile t, int label);
	void replaceValue(grid &g, int a, int b);
	grid labelConnectedComponents(grid g);
	void connectTiles(grid &g, tile t1, tile t2);
	void connectGrid(grid &g, grid ccLabelledGrid);

	Map generate(int w, int h);
}