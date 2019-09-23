#include "main.h"
#include <SDL2/SDL.h>
#include "Window.h"
#include "Brick.h"
#include "Location.h"
#include "Snake.h"
#include "Rect.h"
#include "Board.h"
#include "Menu.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <chrono>

//Dimensions of the screen
const int SCREEN_WIDHT = 800;
const int SCREEN_HEIGHT = 600;

//Create an enum for game states
enum GameState gameState = MenuActive;

//Poll events function
void pollEvents(Window &Win, Menu &M, std::stack<Board> &G) {
    
    //One SDL_Event for every object
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		Win.PollEvents(event);
        if (gameState == MenuActive) {
        M.PollEvents(event);
        }
        if (!G.empty()) {
            G.top().PollEvents(event);
        }
	}
}

int main(int argc, char **argv)
{
    Window window("Pithon");
    
    Menu menu(Window::renderer, SCREEN_WIDHT, SCREEN_HEIGHT, "new_images/menu_background.png", "new_images/play_menu_background.png", "new_images/info_image.png", "fonts/Pacifico.ttf");
    
    //Create a vector of Rects to represent the bricks and the snake
    int oneBrickDimension = 50;
    std::vector<std::unique_ptr<Rect>> rectangles;
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/0.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/1.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/2.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/3.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/4.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/5.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/6.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/7.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/8.png"));
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/9.png"));
    //Number 10 stands for 3, (the head of the snake)
    rectangles.push_back(std::make_unique<Rect>(Window::renderer, oneBrickDimension, oneBrickDimension, "new_images/10.png"));
    
    
    //Create a stack for the board
    std::stack<Board> game;
    
    //This is set to current time when gameState is changing to GameOver - it enable to wait a few seconds for game over communication to display
    std::chrono::time_point<std::chrono::system_clock> gameStateChangeToGameOverTime;

    //Game loop
	while (!window.IsClosed()) {
        
        //******Handle events*****
		pollEvents(window, menu, game);
        
        
        //******Update******
        //Start game if it's chosen
        if (gameState == EasyLevelChosen) {
            bool hardLvl = false;
            game.push(Board(Window::renderer, "fonts/Pacifico.ttf", hardLvl, SCREEN_WIDHT, SCREEN_HEIGHT, oneBrickDimension));
            gameState = EasyLevelPlaying;
        }
        if (gameState == HardLevelChosen) {
            bool hardLvl = true;
            game.push(Board(Window::renderer, "fonts/Pacifico.ttf", hardLvl, SCREEN_WIDHT, SCREEN_HEIGHT, oneBrickDimension));
            gameState = HardLevelPlaying;
        }
        
        //Update the game if it's running
        if (!game.empty()) {
            game.top().Update();
        }
        
        //Check if game is over - if it is a change of the game state
        if (!game.empty() && gameState != GameOver) {   //second condition is for execute code inside only once
            if (game.top().IsGameOver() == true) {
                gameState = GameOver;
                gameStateChangeToGameOverTime = std::chrono::system_clock::now();
            }
        }
        
        //If game state is GameOver, wait a few second for communication to display
        //and pop this board from the stack. Then change the game state to MenuActive.
        auto timeFromGameOver = std::chrono::system_clock::now() - gameStateChangeToGameOverTime;
        if (!game.empty() && gameState == GameOver && timeFromGameOver >= std::chrono::seconds{5}) {
            game.pop();
            gameState = MenuActive;
        }
        
        //Window checks if game was closed by click 'Exit'
        window.CheckExit();
        
        
        //******Draw******
        //Draw menu
        if (gameState == MenuActive) {
            menu.Draw(Window::renderer);
        }
        
        //Draw board
        if (!game.empty()) {
            game.top().Draw(Window::renderer, rectangles, "fonts/Pacifico.ttf", timeFromGameOver);
        }
        
		window.Clear();
	}

	return 0;
}
