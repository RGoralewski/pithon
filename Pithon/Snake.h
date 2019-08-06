//
//  Snake.h
//  Pithon
//
//  Created by Radek on 18/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#ifndef Snake_h
#define Snake_h

#include <SDL2/SDL.h>
#include "Brick.h"
#include "Location.h"
#include <vector>
#include <memory>

class Rect;
class Board;

class Snake {
    friend Board; //for Board's PollEvents method
public:
    //Constructor creates Snake's head (first Brick in the vector)
    Snake(int _number, Location _location, int _xDir, int _yDir);
    ~Snake();
    
    //Build on the snake by adding another Brick to the vector
    void Build(Brick &b);
    
    //Move a Snake by one position on the Board in current Snake's direction
    void Move();
    
    //Change direction of the Snake movement
    void ChangeDirection(int _xDir, int _yDir);
    
    //Get snake's lenght
    int GetLength();
    
    //Get brick's location
    Location GetLocation(int n);
    
    //Draw the snake
    void Draw(SDL_Renderer* renderer, std::vector<std::unique_ptr<Rect>> &rects, int oneBrickDimension);

private:
    //A vector of Bricks forms a snake
    std::vector<Brick> snake;

    //Direction of Snake movement (x and y component may be -1, 0 or 1)
    int xDir, yDir;
    
};

#endif /* Snake_h */
