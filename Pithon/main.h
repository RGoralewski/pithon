//
//  main.h
//  Pithon
//
//  Created by Radek on 20/08/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#ifndef main_h
#define main_h

//Create an enum for game states
enum GameState {
    MenuActive,
    EasyLevelChosen,
    HardLevelChosen,
    EasyLevelPlaying,
    HardLevelPlaying,
    GameOver,
    Exit
};

//Global variable - main.cpp and Menu, Window classes uses this
extern enum GameState gameState;

#endif /* main_h */
