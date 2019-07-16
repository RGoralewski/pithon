#include "Window.h"
#include "Rect.h"
#include "Text.h"


void pollEvents(Window &Win, Rect &Rec) {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		Win.PollEvents(event);
		Rec.PollEvents(event);
	}
}

int main(int argc, char **argv)
{
	Window window("Pithon");
	Rect rect(Window::renderer, 200, 170, 100, 100, "images/siema.png");
	Text text(Window::renderer, "Pacifico.ttf", 40, "Hello universe!", { 0,0,255,255 });

	while (!window.IsClosed()) {
		pollEvents(window, rect);
		rect.Draw(Window::renderer);
		text.Draw(20, 20, Window::renderer);
		window.Clear();
	}

	return 0;
}
