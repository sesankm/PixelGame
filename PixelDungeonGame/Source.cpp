#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
	Game g((char*) "Grimline", 100, 100, 900, 700);
	g.add_layer((char*)"Map_Floor.csv", (char*) "tileset.png");
	g.add_layer((char*)"Map_Trees.csv", (char*) "tileset.png");
 	g.add_layer((char*)"Map_Stones.csv", (char*) "tileset.png");
 	g.add_layer((char*)"Map_Decor.csv", (char*) "tileset.png");
	g.layers[1].collision_layer = true;
	g.run();
	return 0;
}
