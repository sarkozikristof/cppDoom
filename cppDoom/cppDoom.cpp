#include <iostream>
#include "WADLoader.h"

int main() {
	WADLoader wadloader("resources\\DOOM.WAD");
	wadloader.LoadWAD();

	return 0;
}