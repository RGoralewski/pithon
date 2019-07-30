#pragma once

#include "Window.h"

#include <string>

class Rect {
public:
	Rect(int _w, int _h, int _r, int _g, int _b, int _a);
	Rect(SDL_Renderer *renderer, int _w, int _h, const std::string &image_path);
	~Rect();

	void Draw(SDL_Renderer *renderer, int x, int y);

private:
	int w, h;
	int r, g, b, a;
	SDL_Texture *texture;
};
