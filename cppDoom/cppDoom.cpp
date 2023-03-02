#include <iostream>
#include "WADLoader.h"
#include "Map.h"

int main() {
	WADLoader wadloader("DOOM.WAD");
	wadloader.LoadWAD();

	Map map("E1M1");
	wadloader.LoadMapData(map);

	return 0;
}