#include "pch.h"
#include "Map.h"
#include "MapGenerator.h"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <list>

Map::~Map()
{
}

void Map::display() {
	for (auto row : grid) {
		for (auto t : row) {
			cout << t << ' ';
		}
		cout << endl;
	}
}

Map Map::generate(int w, int h) {
	return MapGenerator::generate(w, h);
}

Map Map::generate(int n) {
	return generate(n, n);
}

Map Map::generate() {
	return generate(10, 10);
}