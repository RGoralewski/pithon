//
//  Board.cpp
//  Pithon
//
//  Created by Radek on 30/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "Board.h"
#include "Rect.h"



Board::Board(bool _piKnowerMode, int screenWidth, int screenHeight, int _dimensionOfOneBrick, Location snakeLocation, int xDir, int yDir, double _snakeSpeed) :
    piKnowerMode(_piKnowerMode), dimensionOfOneBrick(_dimensionOfOneBrick), snake(3, snakeLocation, xDir, yDir), snakeSpeed(_snakeSpeed)
{
    nColumns = screenWidth/dimensionOfOneBrick;
    nRows = screenHeight/dimensionOfOneBrick;
    
    //Initialize time
    lastMovementTime = std::chrono::system_clock::now();
    
    gameOver = false;
    
    if (piKnowerMode) {
        //Add one correct and two wrong bricks
        AddCorrectBrick();
        AddWrongBrick();
        AddWrongBrick();
    }
    else {
        //Add the first brick to collect
        AddCorrectBrick();
    }
}

Board::~Board()
{
}

int Board::nextPi() {
    int i = snake.GetLength() - 1;
    return PI_DEC_EXP[i];
}

Location Board::findNotOccupiedLocation() {
    
    int xLoc, yLoc;
    
    //Try to find right location
    bool goodLoc;
    do
    {
        //Set random location
        xLoc = rand()%nColumns;
        yLoc = rand()%nRows;
        
        //Check if this location is occupied by the snake
        goodLoc = true;
        for (int i = 0; i < snake.GetLength(); i++){
            if (snake.GetLocation(i).x == xLoc && snake.GetLocation(i).y == yLoc){
                goodLoc = false;
            }
        }
    } while (!goodLoc);
    
    return {xLoc, yLoc};
}

void Board::AddCorrectBrick() {

    //Find location for the new brick
    Location newLoc = findNotOccupiedLocation();
    
    //The next number for the snake to collect
    int n = nextPi();
    
    //Add a brick
    bricks.push_back(Brick(n, newLoc));
}

void Board::AddWrongBrick() {
    
    //Find location for the new brick
    Location newLoc = findNotOccupiedLocation();
    
    //Find a number which is not the next pi number
    int n;
    int nPi = nextPi();
    do
    {
        n = rand()%10;
    } while (n == nPi);
    
    //Add a brick
    bricks.push_back(Brick(n, newLoc));
}

void Board::Update() {
    //If there's been more then 1/snakeSpeed seconds from last move
    auto timeLimit = 1/snakeSpeed * std::chrono::seconds{1};
    auto now = std::chrono::system_clock::now();
    if (now - lastMovementTime > timeLimit) {
        //Move the snake
        snake.Move();
        //Save movement time
        lastMovementTime = now;
    }
    
    //Check if there is a collision between the snake and a brick
    for (int i = 0; i < snake.GetLength(); i++) {
        for (int j = 0; j < bricks.size(); j++) {
            if (snake.GetLocation(i).x == bricks[j].GetLocation().x && snake.GetLocation(i).y == bricks[j].GetLocation().y) {
                //Is it the right brick number?
                if (bricks[j].GetNumber() == nextPi()) {
                    //If it is add the brick to snake and clear the bricks vector
                    snake.Build(bricks[j]);
                    bricks.clear();
                    
                    
                    //Create a new bricks to collect depending on game mode
                    if (piKnowerMode) {
                        AddCorrectBrick();
                        AddWrongBrick();
                        AddWrongBrick();
                    }
                    else {
                        AddCorrectBrick();
                    }
                }
                else {
                    gameOver = true;
                }
            }
        }
    }
    
    //Check if the snake gets out the board
    if (snake.GetLocation(0).x < 0 || snake.GetLocation(0).x >= nColumns || snake.GetLocation(0).y < 0 || snake.GetLocation(0).y >= nRows) {
        gameOver = true;
    }
}

void Board::PollEvents(SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (snake.yDir != 1)
                        snake.ChangeDirection(0, -1);
                    break;
                    
                case SDLK_DOWN:
                    if (snake.yDir != -1)
                        snake.ChangeDirection(0, 1);
                    break;
                    
                case SDLK_LEFT:
                    if (snake.xDir != 1)
                        snake.ChangeDirection(-1, 0);
                    break;
                    
                case SDLK_RIGHT:
                    if (snake.xDir != -1)
                        snake.ChangeDirection(1, 0);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void Board::Draw(SDL_Renderer* renderer, std::vector<std::unique_ptr<Rect>> &rects){
    //Draw the snake
    snake.Draw(renderer, rects, dimensionOfOneBrick);
    
    //Draw the bricks
    for (auto &b: bricks) {
        b.Draw(renderer, rects, dimensionOfOneBrick);
    }
}
