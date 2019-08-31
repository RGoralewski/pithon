//
//  Menu.h
//  Pithon
//
//  Created by Radek on 10/08/2019.
//  Copyright © 2019 Radek. All rights reserved.
//

#ifndef Menu_h
#define Menu_h

#include <SDL2/SDL.h>
#include "Text.h"
#include "Rect.h"
#include <string>

#define MAX_MAIN_MENU_ITEMS 3
#define MAX_PLAY_MENU_ITEMS 2



class Menu
{
public:
    Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight, const std::string &menuBackgroundPath, const std::string &infoImagePath, const std::string &itemsFontPath);
    ~Menu();
    
    void PollEvents(SDL_Event &event);
    
    void Draw(SDL_Renderer* renderer);
    
    
private:
    Rect menuBackground;
    Rect infoImage;
    Text mainMenuItems[MAX_MAIN_MENU_ITEMS];
    Text playMenuItems[MAX_PLAY_MENU_ITEMS];
    
    //Selected item is marked by red color, the others are white
    int selectedItem;
    
    //Booleans to know where we are
    bool inMainMenu, inPlayMenu, inInfo;
    
    //Static variables for colors
    static SDL_Color red, white;
    
    //And one for font size
    static int fontSize;
    
    //***********
    
    //Private methods to changing selected item
    void MoveUp();
    void MoveDown();
    
    //Private method to execute the selected item
    void ExecuteItem();
    
    //Private method to return to main manu from play menu
    void ReturnToMainMenu();
};

#endif /* Menu_h */
