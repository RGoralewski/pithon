//
//  Menu.cpp
//  Pithon
//
//  Created by Radek on 10/08/2019.
//  Copyright © 2019 Radek. All rights reserved.
//
#include "Menu.h"
#include "main.h"
#include <stdio.h>
#include <iostream>


SDL_Color Menu::red = {190, 48, 37};
SDL_Color Menu::white = {255, 255, 255};
int Menu::fontSize = 40;


Menu::Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight, const std::string &menuBackgroundPath,
        const std::string &playMenuBackgroundPath, const std::string &infoImagePath, const std::string &itemsFontPath) :
//Create main menu background image
menuBackground(renderer, screenWidth, screenHeight, menuBackgroundPath),

//Create play menu background image
playMenuBackground(renderer, screenWidth, screenHeight, playMenuBackgroundPath),

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
                inPlayMenu = true;
                playMenuItems[0].ModulateColor(red);
                break;
                
            //Click on 'Info' cause info showing
            case 1:
                inMainMenu = false;
                inInfo = true;
                break;
                
            //Click on 'Exit' change game state to Exit
            case 2:
                gameState = Exit;
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
                gameState = EasyLevelChosen;
                inPlayMenu = false;
                inMainMenu = true;
                break;
                
            //Click on 'Hard level' cause communication displaying
            case 1:
                gameState = HardLevelChosen;
                inPlayMenu = false;
                inMainMenu = true;
                selectedItem = 0;
                playMenuItems[1].ModulateColor(white);
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
    
    
    //Display main menu
    if (inMainMenu) {
        //Display the background
        menuBackground.Draw(renderer, 0, 0);
        
        //Display options
        int yDrawPosition = 50;
        for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
            mainMenuItems[i].Draw(50, yDrawPosition, renderer);
            yDrawPosition += mainMenuItems[i].GetHeight() + 20;
        }
    }
    
    //Display play menu
    if (inPlayMenu) {
        //Display the background
        playMenuBackground.Draw(renderer, 0, 0);
        
        //Display options
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
