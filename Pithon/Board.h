//
//  Board.h
//  Pithon
//
//  Created by Radek on 30/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <SDL2/SDL.h>
#include "Snake.h"
#include "Brick.h"
#include "Text.h"
#include <vector>
#include <chrono>

//Decimal expansion of pi in an array
static const int PI_ACCURACY = 72;
static int PI_DEC_EXP[PI_ACCURACY] = { 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6 };

class Board
{
public:
    Board(SDL_Renderer* renderer = nullptr, const std::string &fontPath = "fonts/Pacifico.ttf", bool _piKnowerMode = false, int screenWidth = 800, int screenHeight = 600, int _dimensionOfOneBrick = 40, Location snakeLocation = {5, 2}, int xDir = 0, int yDir = 1, double _snakeSpeed = 5);
    ~Board();
    
    //Move the snake and check if it collect a brick
    void Update();
    
    //Handle events
    void PollEvents(SDL_Event &event);

    //Draw the board
    void Draw(SDL_Renderer* renderer, std::vector<std::unique_ptr<Rect>> &rects, const std::string &fontPath,
              std::__1::chrono::duration<long long, std::__1::ratio<1, 1000000> > timeFromGameOver);
    
    //Return gameOver
    inline bool IsGameOver() { return gameOver; }
    
private:
    //Define the difficulty level of game (when piKnowerMode is disabled, player collect the bricks one by one and learn the decimal expandion of pi; when piKnowerMode is endabled, player see three bricks in one time and he has to choose the one with the correct next pi's decimal expansion number)
    bool piKnowerMode;
    
    //Snake
    Snake snake;
    
    //Bricks to collect
    std::vector<Brick> bricks;
    
    //Bricks dimensions
    int dimensionOfOneBrick;
    
    //Number of columns and rows (depend on screen dimensions and one brick dimension)
    int nColumns, nRows;
    
    //Snake's speed (in locations per second)
    double snakeSpeed;
    
    //Last snake's movement time
    std::chrono::time_point<std::chrono::system_clock> lastMovementTime;
    
    //True when the snake collects a wrong brick, hits itself or gets out the board
    bool gameOver;
    
    //Tells if game is over because of collecting a wrong number
    bool wrongNumberGameOver;
    
    //Communications to draw when the game is over
    Text crashCommunication;
    Text wrongNumberCommunication;
    
    //*************
    
    //Return the next right pi number depending how many pi number snake has already collected
    int nextPi();
    
    //Return location not occupied by the snake
    Location findNotOccupiedLocation();
    
    //Add a brick with a number which is the next decimal expansion of pi
    void AddCorrectBrick();
    
    //Add a brick with a number which is NOT the next decimal expansion of pi
    void AddWrongBrick();
};

#endif /* Board_h */
