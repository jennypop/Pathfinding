#include "pch.h"
#include "Map.h"
#include <iostream>
using namespace std;

int main()
{
	Map map1 = Map::generate();
	Map map2 = Map::generate(5);
	Map map3 = Map::generate(6, 10);
	Map map4 = Map::generate(25, 25);
	map1.display();
	cout << endl;
	map2.display();
	cout << endl;
	map3.display();
	cout << endl;
	map4.display();
}