#pragma once

#include "Window.h"

#include <string>

class Rect {
public:
	Rect(int _w, int _h, int _x, int _y, int _r, int _g, int _b, int _a);
	Rect(SDL_Renderer *renderer, int _w, int _h, int _x, int _y, const std::string &image_path);
	~Rect();

	void Draw(SDL_Renderer *renderer);

	void PollEvents(SDL_Event &event);

private:
	int w, h;
	int x, y;
	int r, g, b, a;
	SDL_Texture *texture;
};
