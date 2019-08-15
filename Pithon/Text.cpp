#include "Text.h"
#include <iostream>


Text::Text(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string &messageText, const SDL_Color &color)
{
	textTexture = LoadFont(renderer, fontPath, fontSize, messageText, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::Draw(int x, int y, SDL_Renderer *renderer) {
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture *Text::LoadFont(SDL_Renderer *renderer, const std::string &fontPath, int fontSize, const std::string &messageText, const SDL_Color &color) {
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		std::cerr << "Failed to load font" << std::endl;
	}
	auto textSurface = TTF_RenderText_Solid(font, messageText.c_str(), color);
	if (!textSurface) {
		std::cerr << "Failed to create text surface" << std::endl;
	}
	auto _textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!_textTexture) {
		std::cerr << "Failed to create text texture" << std::endl;
	}
	SDL_FreeSurface(textSurface);
	return _textTexture;
}

void Text::ModulateColor(SDL_Color &color) {
    SDL_SetTextureColorMod(textTexture, color.r, color.g, color.b);
}
