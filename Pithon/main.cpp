#include <SDL2/SDL.h>
#include "Window.h"
#include "Brick.h"
#include "Location.h"
#include "Snake.h"
#include "Rect.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <memory>

void pollEvents(Window &Win, Board &B) {
    //One SDL_Event for every object
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		Win.PollEvents(event);
        B.PollEvents(event);
	}
}


int main(int argc, char **argv)
{
    Window window("Pithon");
    
    //Create a vector of Rects to represent the bricks and the snake
    int oneBrickDimension = 40;
    std::vector<std::unique_ptr<Rect>> rectangles;
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/0.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/1.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/2.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/3.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/4.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/5.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/6.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/7.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/8.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "images/9.png"));
    
    
    //Create a board
    bool hardLvl = true;
    Board board = Board(Window::renderer, "fonts/Pacifico.ttf", hardLvl, 800, 600, oneBrickDimension);
    
    
    
	while (!window.IsClosed()) {
        //Handle events
		pollEvents(window, board);
        
        //Update
        board.Update();
        
        //Draw
        board.Draw(Window::renderer, rectangles);
		window.Clear();
	}

	return 0;
}
