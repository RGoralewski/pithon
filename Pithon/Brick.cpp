//
//  Brick.cpp
//  Pithon
//
//  Created by Radek on 16/07/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#include "Brick.h"
#include <stdio.h>

Brick::Brick(int _number, Location _loc)
{
    number = _number;
    location = _loc;
}

Brick::~Brick()
{
}

void Brick::Draw(SDL_Renderer* renderer, std::vector<std::unique_ptr<Rect>> &rects, int brickDimension) {
    if (number < rects.size()) {
        rects[number] -> Draw(renderer, brickDimension * location.x, brickDimension * location.y);
    }
}
