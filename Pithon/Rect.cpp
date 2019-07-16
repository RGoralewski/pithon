#include "Rect.h"

#include <SDL2_image/SDL_image.h>
#include <iostream>


Rect::Rect(int _w, int _h, int _x, int _y, int _r, int _g, int _b, int _a) :
	w(_w), h(_h), x(_x), y(_y), r(_r), g(_g), b(_b), a(_a)
{
}

Rect::Rect(SDL_Renderer *renderer, int _w, int _h, int _x, int _y, const std::string &image_path) :
	w(_w), h(_h), x(_x), y(_y)
{
	texture = nullptr;

	//Create surface
	auto surface = IMG_Load(image_path.c_str());
	if (!surface) {
		std::cerr << "Failed to create surface." << std::endl;
	}

	//Create texture
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create texture." << std::endl;
	}
	
	//Get rid of surface
	SDL_FreeSurface(surface);
}

Rect::~Rect() 
{
	SDL_DestroyTexture(texture); 
}

void Rect::Draw(SDL_Renderer *renderer) {
	SDL_Rect rect = { x, y, w, h };
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
	else {
		SDL_SetRenderDrawColor(Window::renderer, r, g, b, a);
		SDL_RenderFillRect(Window::renderer, &rect);
	}
}

void Rect::PollEvents(SDL_Event &event) {
	
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			x -= 10;
			break;

		case SDLK_RIGHT:
			x += 10;
			break;

		case SDLK_UP:
			y -= 10;
			break;

		case SDLK_DOWN:
			y += 10;
			break;
		}
	}
}
