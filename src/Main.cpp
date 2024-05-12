#include <iostream>
#include "GameBoy.h"
#include "CPU/CPU.h"

int main() {
	GameBoy* gameBoy = new GameBoy();
	gameBoy->emulate();
	return 0;
}