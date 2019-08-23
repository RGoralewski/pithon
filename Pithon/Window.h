#pragma once

#include <string>
#include <SDL2/SDL.h>

class Window {
public:
	Window(const std::string &_title = "Window", int _width = 800, int _height = 600);
	~Window();

	//Return if window is close
	inline bool IsClosed() { return closed; }

	//Handle events
	void PollEvents(SDL_Event &event);
    
    //Checks if key exit was pressed (by checking the game state)
    void CheckExit();

	//Clean a window
	void Clear();

private:
	//Parameters of a window
	std::string title;
	int width;
	int height;

	//Keeps track whether window is closed
	bool closed;

	//Window by SDL
	SDL_Window *window;


	//Initialing method
	bool Init();

public:
	//Renderer
	static SDL_Renderer *renderer;
};
