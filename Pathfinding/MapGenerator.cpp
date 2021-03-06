#include "pch.h"
#include "Map.h"
#include "MapGenerator.h"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <list>

namespace MapGenerator {

	// a grid with values 0 (space) and 1 (obstacle)
	grid generateUnconnectedGrid(int w, int h) {
		grid g;
		for (int i = 0; i < w; ++i) {
			vector<int> row;
			for (int j = 0; j < h; ++j) {
				int val = min(rand() % 5, 1);	// 1 in 5 times val = 0
				row.push_back(1 - val);
			}
			g.push_back(row);
		}
		return g;
	}

	tile findTileWithValue(grid g, int v) {
		for (size_t i = 0; i < g.size(); ++i) {
			for (size_t j = 0; j < g[0].size(); ++j) {
				if (g[i][j] == v) return pair<int, int>(i, j);
			}
		}
		return pair<int, int>(-1, -1);
	}

	bool inBounds(tile t, grid g) {
		int w = g[0].size(); int h = g.size();
		return (t.first >= 0 && t.first < h && t.second >= 0 && t.second < w);
	}

	// only applies to tiles of value 0, which represents unlabelled land
	void floodFill(grid &g, tile t, int label) {
		g[t.first][t.second] = label;

		tile n = tile(t); n.first = t.first - 1;
		tile w = tile(t); w.second = t.second - 1;
		tile e = tile(t); e.second = t.second + 1;
		tile s = tile(t); s.first = t.first + 1;

		if (inBounds(n, g) && g[n.first][n.second] == 0) floodFill(g, n, label);
		if (inBounds(w, g) && g[w.first][w.second] == 0) floodFill(g, w, label);
		if (inBounds(e, g) && g[e.first][e.second] == 0) floodFill(g, e, label);
		if (inBounds(s, g) && g[s.first][s.second] == 0) floodFill(g, s, label);
	}

	void replaceAll(grid &g, int a, int b) {
		for (size_t i = 0; i < g.size(); ++i) {
			for (size_t j = 0; j < g[0].size(); ++j) {
				if (g[i][j] == a) g[i][j] = b;
			}
		}
	}

	// returns a new grid showing connected components of non-obstacle space in g:
	// where connected components of space are labelled by numbers (1,2...)
	// obstacles are labelled -1
	grid labelConnectedComponents(grid g) {
		auto ccLabelledGrid(g);
		replaceAll(ccLabelledGrid, 1, -1);
		int ccCount = 0;
		tile t = findTileWithValue(g, 0);
		while (t.first >= 0) {					// while t is a valid tile
			ccCount++;
			floodFill(ccLabelledGrid, t, ccCount);
			t = findTileWithValue(ccLabelledGrid, 0);
		}
		return ccLabelledGrid;
	}

	// creates an obstacle-free path (of 0s) between two tiles
	void connectTiles(grid &g, tile t1, tile t2) {
		tile current = tile(t1);
		while (current != t2) {
			int xdiff = t2.second - current.second;
			int ydiff = t2.first - current.first;
			g[current.first][current.second] = 0;
			if (xdiff != 0 && (rand() % 2 == 0)) {
				if (xdiff > 0) {current.second++; }
				else { current.second--; }
			}
			else if (ydiff != 0) {
				if (ydiff > 0) { current.first++; }
				else if (ydiff < 0) { current.first--; }
			}
		}
	}

	// takes: grid g, grid ccLabelledGrid of connected components of g.
	// modifies g so that all the land '0' tiles are connected
	void connectGrid(grid &g, grid ccLabelledGrid) {
		list<tile> componentTileList;
		tile x = findTileWithValue(ccLabelledGrid, 1);
		for (int i = 2; x.first >= 0; ++i) {
			componentTileList.push_back(x);
			x = findTileWithValue(ccLabelledGrid, i);
		}

		auto it = componentTileList.begin();
		while (next(it) != componentTileList.end()) {
			connectTiles(g, *it, *next(it));
			it++;
		}
	}

	Map generate(int w, int h) {
		grid g = generateUnconnectedGrid(w, h);
		connectGrid(g, labelConnectedComponents(g));
		return g;
	}
}