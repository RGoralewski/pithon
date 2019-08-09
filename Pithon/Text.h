#pragma once

#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>

class Text {
public:
	Text(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string &messageText, const SDL_Color &color);

	void Draw(int x, int y, SDL_Renderer *renderer);

	static SDL_Texture *LoadFont(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string &messageText, const SDL_Color &color);
    
    inline int GetWidth() {return textRect.w;}
    inline int GetHeight() {return textRect.h;}

private:
	SDL_Texture *textTexture;
	SDL_Rect textRect;
};
