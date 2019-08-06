#include "Window.h"

#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>


SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string &_title, int _width, int _height) 
{
	title = _title;
	width = _width;
	height = _height;
	closed = false;
	window = nullptr;

	//Initialize and create a window
	closed = !Init();
}

Window::~Window() 
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::Init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL." << std::endl;
		return false;
	}

	//Initialize SDL_image (for PNGs)
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "Failed to initialize SDL_image." << std::endl;
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize SDL_ttf." << std::endl;
		return false; 
	}

	//Create window
	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);

	if (window == nullptr) {
		std::cerr << "Failed to create window" << std::endl;
		return false;
	}

	//Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer" << std::endl;
		return false;
	}

	return true;
}



void Window::PollEvents(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		closed = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {

		case SDLK_ESCAPE:
			closed = true;
			break;

		default:
			break;
		}

	case SDL_MOUSEMOTION:
		//std::cout << event.motion.x << ", " << event.motion.y << std::endl;
		break;

	default:
		break;
	}
}

void Window::Clear() {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
}
