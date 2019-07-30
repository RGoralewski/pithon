//
//  Brick.h
//  Pithon
//
//  Created by Radek on 16/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//


#ifndef Brick_h
#define Brick_h

#include "Location.h"

class Snake;

class Brick
{
    friend Snake;
public:
    Brick(int _number, Location _loc);
    ~Brick();
    
    //Get a location
    inline Location GetLocation() { return location; }
    
    //Get a number
    inline int GetNumber() { return number; }
    
private:
    
    //Number on a Brick
    int number;
    
    //Position on a Board
    Location location;
};

#endif /* Brick_h */
