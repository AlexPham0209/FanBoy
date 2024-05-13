#include <iostream>
#include "../src/GameBoy.h"

int main() {
	GameBoy* gameBoy = new GameBoy();
	gameBoy->emulate();
	delete gameBoy;

	return 0;
}