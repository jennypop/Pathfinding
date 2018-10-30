//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
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

TEST_CASE("floodFill 2x1 test", "[mapgeneration]") {
	grid g{ {0,0}};
	tile t = pair<int, int>(0, 0);
	floodFill(g, t, 2);
	for (auto row : g) for (auto t : row) {
		REQUIRE(t == 2);
	}
}

TEST_CASE("floodFill 2x2 test", "[mapgeneration]") {
	grid g{ {0,0}, {1,0} };
	tile t = pair<int, int>(0, 0);
	floodFill(g, t, 2);
	grid expected{ {2, 2}, { 1,2 } };
	REQUIRE(g == expected);
}

TEST_CASE("floodFill 3x3 test", "[mapgeneration]") {
	grid g{ {0,0,1}, {0,0,1}, {0,1,0} };
	tile t = pair<int, int>(1, 1);
	floodFill(g, t, 2);
	grid expected{ {2,2,1}, {2,2,1}, {2,1,0} };
	REQUIRE(g == expected);
}

TEST_CASE("labelConnectedComponents 001 test", "[mapgeneration]") {
	grid g{ {0,0,1} };
	grid res = labelConnectedComponents(g);
	grid expected{ {1,1,-1} };
	REQUIRE(res == expected);
}

TEST_CASE("labelConnectedComponents 010 test", "[mapgeneration]") {
	grid g{ {0,1,0}};
	grid res = labelConnectedComponents(g);
	grid expected{ {1,-1,2} };
	REQUIRE(res == expected);
}

TEST_CASE("labelConnectedComponents 3x3 test", "[mapgeneration]") {
	grid g{ {0,0,1}, {0,0,1}, {0,1,0} };
	grid res = labelConnectedComponents(g);
	grid expected{ {1, 1, -1}, { 1,1,-1 }, { 1,-1,2 } };
	REQUIRE(res == expected);
}

TEST_CASE("labelConnectedComponents 3x3 test2", "[mapgeneration]") {
	grid g{ {0,1,0}, {1,1,1}, {0,1,0} };
	grid res = labelConnectedComponents(g);
	grid expected{ {1, -1, 2}, { -1,-1,-1 }, { 3,-1,4 } };
	REQUIRE(res == expected);
}

TEST_CASE("connectTiles basic test", "[mapgeneration]") {
	grid g{ {0,1,0} };
	tile t1 = pair<int, int>(0, 0);
	tile t2 = pair<int, int>(0, 2);
	connectTiles(g, t1, t2);
	grid expected{ {0,0,0} };
	REQUIRE(g == expected);
}

// since connectTiles is automated I can't specify the exact result, so this
// test just logs the output
TEST_CASE("connectTiles display test1", "[mapgeneration]") {
	grid g{ {1,0},{0,1} };
	tile t1 = pair<int, int>(0, 1);
	tile t2 = pair<int, int>(1, 0);
	connectTiles(g, t1, t2);
	for (auto row : g) {
		for (auto t : row) {
			cout << t;
		}
		cout << endl;
	}
}

TEST_CASE("connectTiles display test2", "[mapgeneration]") {
	grid g{ {0,1,1},{1,1,1},{1,1,0} };
	tile t1 = pair<int, int>(0, 0);
	tile t2 = pair<int, int>(2, 2);
	connectTiles(g, t1, t2);
	for (auto row : g) {
		for (auto t : row) {
			cout << t;
		}
		cout << endl;
	}
}

TEST_CASE("connectGrid basic test", "[mapgeneration]") {
	grid g{ {0,1,0} };
	grid ccs{ {1,-1,2} };
	grid expected{ {0,0,0} };
	connectGrid(g, ccs);
	REQUIRE(g == expected);
}

TEST_CASE("connectGrid display test", "[mapgeneration]") {
	grid g{ {0,1,0}, {1,1,1}, {0,1,0} };
	grid ccs{ {1,-1,2},{-1,-1,-1},{3,-1,4} };
	connectGrid(g, ccs);
	for (auto row : g) {
		for (auto t : row) {
			cout << t;
		}
		cout << endl;
	}
}