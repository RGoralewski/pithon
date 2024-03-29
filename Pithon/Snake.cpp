//
//  Snake.cpp
//  Pithon
//
//  Created by Radek on 18/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#include "Snake.h"
#include "Rect.h"
#include <iostream>
#include <memory>

Snake::Snake(int _number, Location _location, int _xDir, int _yDir)
{
    xDir = 0;
    yDir = 0;
    
    //Set initial direction
    ChangeDirection(_xDir, _yDir);
    
    //Create a snake head (first Brick)
    Brick b(_number, _location);
    snake.push_back(b);
}

Snake::~Snake()
{
}

void Snake::Build(Brick &b, Location l) {
    //Change the location of the brick
    b.location = l;
    
    //Add to the vector
    snake.push_back(b);
}

void Snake::Move(){
    //Move the snake - each Brick is located in the place of previous Brick
    for (int n = int(snake.size()) - 1; n >= 0; n--) {
        if (n == 0) {
            //Move head of the snake according to it's direction
            snake[n].location.x += xDir;
            snake[n].location.y += yDir;
        }
        else {
            //Get Location of previous Brick
            Location tmpL = snake[n-1].location;
        
            //Set new Location of another Bricks
            snake[n].location = tmpL;
        }
    }
}

void Snake::ChangeDirection(int _xDir, int _yDir) {
    //Set x direction
    if (_xDir==-1 || _xDir==0 || _xDir==1)
        xDir = _xDir;
    else
        std::cerr << "Cannot set x direction of the Snake! This value can be only -1, 0 or 1." << std::endl;
    
    //Set y direction
    if (_yDir==-1 || _yDir==0 || _yDir==1)
        yDir = _yDir;
    else
        std::cerr << "Cannot set y direction of the Snake! This value can be only -1, 0 or 1." << std::endl;
}

int Snake::GetLength(){
    return int(snake.size());
}

Location Snake::GetLocation(int n){
    if (n > 0 || n < snake.size()){
        return snake[n].location;
    }
    else {
        std::cout << "Incorrect snake's element number passed to Snake::GetLocation(int n)\n";
        return {-1, -1};
    }
}

void Snake::Draw(SDL_Renderer* renderer, std::vector<std::unique_ptr<Rect>> &rects, int oneBrickDimension) {
    for (auto &s: snake) {
        s.Draw(renderer, rects, oneBrickDimension);
    }
}
