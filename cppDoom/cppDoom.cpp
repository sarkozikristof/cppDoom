#include <iostream>
#include "WADLoader.h"

int main() {
	WADLoader wadloader("DOOM.WAD");
	wadloader.LoadWAD();

	return 0;
}