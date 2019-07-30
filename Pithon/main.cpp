#include <SDL2/SDL.h>
#include "Window.h"
#include "Brick.h"
#include "Location.h"
#include "Snake.h"
#include "Rect.h"
#include <iostream>
#include <vector>
#include <memory>

void pollEvents(Window &Win) {
    //One SDL_Event for every object
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		Win.PollEvents(event);
	}
}

void drawSnake(SDL_Renderer* renderer ,Snake &sn, std::vector<std::unique_ptr<Rect>> &rects, int oneBrickDimension) {
    for (auto &s: sn.snake) {
        if(s.GetNumber()<rects.size()){
            rects[s.GetNumber()]->Draw(renderer, oneBrickDimension * s.GetLocation().x, oneBrickDimension * s.GetLocation().y);
        }
    }
}

int main(int argc, char **argv)
{
    Window window("Pithon");

    //Add a few Bricks in vector
    std::vector<Brick> bricks;
    Brick b1(3, {0, 0});
    bricks.push_back(b1);
    Brick b2(4, {8, 3});
    bricks.push_back(b2);
    Brick b3(8, {6, 3});
    bricks.push_back(b3);
    Brick b4(9, {7, 3});
    bricks.push_back(b4);

    //Create a snake
    Snake pi(3, {5, 2}, 0, 1);
    
    //Create a vector of Rects to represent the Bricks and the Snake
    int oneBrickDimension = 25;
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
    
    
    
    //Snake building test
    int numberToBuild = 3;
    for (auto it = bricks.begin(); it != bricks.end(); ) {
        if (it->GetNumber() == numberToBuild) {
            pi.Build((*it));
            it = bricks.erase(it);
        }
        else {
            it++;
        }
    }
    pi.Move(); //Move a snake
    
    
    
	while (!window.IsClosed()) {
        //Handle events
		pollEvents(window);
        
        //Draw the bricks
        for (auto &b: bricks) {
            if(b.GetNumber()<rectangles.size()){
                rectangles[b.GetNumber()]->Draw(Window::renderer, oneBrickDimension * b.GetLocation().x, oneBrickDimension * b.GetLocation().y);
            }
        }
        //Draw the snake
        drawSnake(Window::renderer, pi, rectangles, oneBrickDimension);
		window.Clear();
	}

	return 0;
}
