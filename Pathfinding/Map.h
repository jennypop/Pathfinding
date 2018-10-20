#pragma once
#include <vector>
using namespace std;

typedef vector<vector<int>> grid;
typedef pair<int, int> tile;

class Map
{
	vector<vector<int>> grid;
public:
	Map(vector<vector<int>> v) : grid(v) {};
	~Map();

	void setGrid(vector<vector<int>> v) {
		grid = v;
	};
	const vector<vector<int>> getGrid() {
		return grid;
	};
	const int getWidth() {
		return grid[0].size();
	};
	const int getHeight() {
		return grid.size();
	};

	void display();
	static Map generate(int w, int h);
	static Map generate(int n);
	static Map generate();
};

