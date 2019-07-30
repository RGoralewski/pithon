#include "Rect.h"

#include <SDL2_image/SDL_image.h>
#include <iostream>


Rect::Rect(int _w, int _h, int _r, int _g, int _b, int _a) :
	w(_w), h(_h), r(_r), g(_g), b(_b), a(_a)
{
}

Rect::Rect(SDL_Renderer *renderer, int _w, int _h, const std::string &image_path) :
	w(_w), h(_h)
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


void Rect::Draw(SDL_Renderer *renderer, int x, int y) {
	SDL_Rect rect = { x, y, w, h };
	if (texture) {
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}
	else {
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderFillRect(renderer, &rect);
	}
}
