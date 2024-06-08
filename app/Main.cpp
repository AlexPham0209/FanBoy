#include <iostream>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"
#include <chrono>
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>


const double DELAY = 0;
int videoPitch;
const int SCALE = 4;
bool running = true;

std::map<int, unsigned char> keyMap;

GameBoy* gameboy;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

bool initWindow() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Gameboy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * SCALE, 144 * SCALE, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "Failed to open window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
		return false;
	}
	std::cout << "Window Created" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr) {
		std::cout << "Failed to create renderer" << std::endl;
		return false;
	}
	std::cout << "Renderer Created" << std::endl;

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
	if (texture == nullptr) {
		std::cout << "Failed to create texture" << std::endl;
		return false;
	}
	std::cout << "Texture Created" << std::endl;

	return true;
}

void render(void const* buffer, int pitch) {
	SDL_UpdateTexture(texture, nullptr, buffer, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void input() {
	SDL_Event e;
	while (SDL_PollEvent(&e) > 0) {
		if (e.type == SDL_QUIT)
			running = false;

		// Process keydown events
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE)
				running = false;

			if (keyMap.count(e.key.keysym.sym)) {
				gameboy->pressButton(keyMap[e.key.keysym.sym]);
			}
		}
		// Process keyup events
		if (e.type == SDL_KEYUP && keyMap.count(e.key.keysym.sym))
			gameboy->releaseButton(keyMap[e.key.keysym.sym]);
	}
}

void run() {
	float time = 0;
	while (running) {
		input();
		gameboy->step();

		if (gameboy->canRender()) {
			unsigned int* frame = gameboy->getFrame();
			int pitch = sizeof(frame[0]) * 160;
			render(frame, pitch);
		}
	}
}

bool init() {
	gameboy = new GameBoy();

	std::string path;
	std::cout << "Enter file path: ";
	std::getline(std::cin, path);

	path.erase(remove(path.begin(), path.end(), '\"'), path.end());
	gameboy->loadGame(path.c_str());
	keyMap[SDLK_LEFT] = GAMEBOY_LEFT;
	keyMap[SDLK_RIGHT] = GAMEBOY_RIGHT;
	keyMap[SDLK_DOWN] = GAMEBOY_DOWN;
	keyMap[SDLK_UP] = GAMEBOY_UP;

	keyMap[SDLK_z] = GAMEBOY_B;
	keyMap[SDLK_x] = GAMEBOY_A; 
	keyMap[SDLK_c] = GAMEBOY_START;
	keyMap[SDLK_v] = GAMEBOY_SELECT;

	if (!initWindow()) {
		std::cout << "Failed to initialize window" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char* args[]) {
	//SDL_SetMainReady();
	if (!init())
		return -1;

	run();

	delete gameboy;
	return 0;
}