//
//  Menu.cpp
//  Pithon
//
//  Created by Radek on 10/08/2019.
//  Copyright © 2019 Radek. All rights reserved.
//
#include "Menu.h"
#include <stdio.h>
#include <iostream>


SDL_Color Menu::red = {255, 0, 0};
SDL_Color Menu::white = {255, 255, 255};
int Menu::fontSize = 40;


Menu::Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight, SDL_Color backgroundColor, const std::string &infoImagePath, const std::string &itemsFontPath) :
//Create the background image
menuBackground(screenWidth, screenHeight, backgroundColor.r, backgroundColor.g, backgroundColor.a, 255),

//Create the info image
infoImage(renderer, screenWidth, screenHeight, infoImagePath),

//Create main menu items ( color - white -> it will be modulate with red to achieve red color)
mainMenuItems{ Text(renderer, itemsFontPath, fontSize, "Play", white),
    Text(renderer, itemsFontPath, fontSize, "Info", white),
    Text(renderer, itemsFontPath, fontSize, "Exit", white)},

//Create play menu items ( color - white -> it will be modulate with red to achieve red color)
playMenuItems{ Text(renderer, itemsFontPath, fontSize, "Easy level", white),
    Text(renderer, itemsFontPath, fontSize, "Hard level", white)
}
{
    //Change first positions' color to red
    mainMenuItems[0].ModulateColor(red);
    playMenuItems[0].ModulateColor(red);
    
    //Selected item is Play (marked red)
    selectedItem = 0;
    
    //In the beggining we are in main menu
    inMainMenu = true;
    inPlayMenu = false;
    inInfo = false;
}

Menu::~Menu()
{
}

void Menu::MoveUp() {
    if (inMainMenu && selectedItem - 1 >= 0) {
        //Change color of current item to white
        mainMenuItems[selectedItem].ModulateColor(white);
        
        //Change selected item
        selectedItem--;
        
        //And change it's color to red
        mainMenuItems[selectedItem].ModulateColor(red);
    }
    
    if (inPlayMenu && selectedItem - 1 >= 0) {
        //Change color of current item to white
        playMenuItems[selectedItem].ModulateColor(white);
        
        //Change selected item
        selectedItem--;
        
        //And change it's color to red
        playMenuItems[selectedItem].ModulateColor(red);
    }
}

void Menu::MoveDown() {
    if (inMainMenu && (selectedItem + 1) < MAX_MAIN_MENU_ITEMS) {
        //Change color of current item to white
        mainMenuItems[selectedItem].ModulateColor(white);
        
        //Change selected item
        selectedItem++;
        
        //And change it's color to red
        mainMenuItems[selectedItem].ModulateColor(red);
    }
    
    if (inPlayMenu && (selectedItem + 1) < MAX_PLAY_MENU_ITEMS) {
        //Change color of current item to white
        playMenuItems[selectedItem].ModulateColor(white);
        
        //Change selected item
        selectedItem++;
        
        //And change it's color to red
        playMenuItems[selectedItem].ModulateColor(red);
    }
}

void Menu::ExecuteItem() {
    //Exectute actions in main menu
    if (inMainMenu) {
        switch (selectedItem) {
            //Click on 'Play' cause move to play menu
            case 0:
                inMainMenu = false;
                mainMenuItems[0].ModulateColor(white);
                inPlayMenu = true;
                playMenuItems[0].ModulateColor(red);
                break;
                
            //Click on 'Info' cause nothing for now
            case 1:
                inMainMenu = false;
                inInfo = true;
                break;
                
            //Click on 'Exit' either
            case 2:
                
                break;
                
            default:
                break;
        }
    }
    
    //Exectute actions in main menu
    else if (inPlayMenu) {
        switch (selectedItem) {
            //Click on 'Easy level' cause communication displaying
            case 0:
                std::cout << "You have run Easy Level!" << std::endl;
                break;
                
            //Click on 'Hard level' cause communication displaying
            case 1:
                std::cout << "You have run Hard Level!" << std::endl;
                break;
                
            default:
                break;
        }
    }
}

void Menu::ReturnToMainMenu() {
    if (inPlayMenu) {
        inPlayMenu = false;
        playMenuItems[selectedItem].ModulateColor(white);
        inMainMenu = true;
        selectedItem = 0;
        mainMenuItems[0].ModulateColor(red);
    }
    else if (inInfo) {
        inInfo = false;
        inMainMenu = true;
    }
}

void Menu::PollEvents(SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                    
                case SDLK_UP:
                    MoveUp();
                    break;
                    
                case SDLK_DOWN:
                    MoveDown();
                    break;
                    
                case SDLK_RETURN:
                    ExecuteItem();
                    break;
                    
                case SDLK_BACKSPACE:
                    ReturnToMainMenu();
                    break;
                    
                default:
                    break;
            }
            
        default:
            break;
    }
}

void Menu::Draw(SDL_Renderer* renderer) {
    
    //Display the background
    menuBackground.Draw(renderer, 0, 0);
    
    //Display main menu
    if (inMainMenu) {
        int yDrawPosition = 50;
        for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
            mainMenuItems[i].Draw(50, yDrawPosition, renderer);
            yDrawPosition += mainMenuItems[i].GetHeight() + 20;
        }
    }
    
    //Display play menu
    if (inPlayMenu) {
        int yDrawPosition = 50;
        for (int i = 0; i < MAX_PLAY_MENU_ITEMS; i++) {
            playMenuItems[i].Draw(50, yDrawPosition, renderer);
            yDrawPosition += playMenuItems[i].GetHeight() + 20;
        }
    }
    
    //Display info
    if (inInfo) {
        infoImage.Draw(renderer, 0, 0);
    }
}