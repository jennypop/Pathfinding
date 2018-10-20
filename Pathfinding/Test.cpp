#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MapGenerator.h"

using namespace std;
using namespace MapGenerator;

TEST_CASE("generateUnconnectedGrid produces mostly land", "[mapgeneration]") {
	grid g = generateUnconnectedGrid(10,10);
	int landCount = 0; int obstacleCount = 0;
	for (auto row : g) for (auto t: row) {
		if (t == 0) landCount++; 
		else if (t == 1) obstacleCount++;
		else throw "value other than 0 or 1 recorded: " + t;
	}
	REQUIRE(landCount > obstacleCount);
}

TEST_CASE("findTileWithValue works correctly", "[mapgeneration]") {
	grid g{ {1,0,1} , {2,1,1} };
	REQUIRE(findTileWithValue(g, 2).first == 1); 
	REQUIRE(findTileWithValue(g, 2).second == 0);

	REQUIRE(findTileWithValue(g, 0).first == 0); 
	REQUIRE(findTileWithValue(g, 0).second == 1);

	REQUIRE(findTileWithValue(g, 3).first == -1); 
	REQUIRE(findTileWithValue(g, 3).second == -1);
}

TEST_CASE("floodFill basic test", "[mapgeneration]") {
	grid g{ {0,0}};
	tile t = pair<int, int>(0, 0);
	floodFill(g, t, 2);
	for (auto row : g) for (auto t : row) {
		REQUIRE(t == 2);
	}
}