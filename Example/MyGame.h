//
//  MyGame.h
//  AAGEngine
//
//  Created by Alex Peixoto on 2/10/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__MyGame__
#define __Action_Adventure_Game_Engine__MyGame__
#ifndef _WIN32
#include <unistd.h>
#endif
#include <iostream>
#include <thread>
#include "Image.h"
#include "Game.h"
#include "LevelManager.h"
#include "ItemManager.h"
#include "SoundEffectManager.h"
#include "ObjectManager.h"
#include "BackgroundShape.h"
#include "InputControl.h"
#include "TextControl.h"
#include "Menu.h"
#include "Dialog.h"

#include "beginMap.h"
#include "closedMap.h"
#include "testMap.h"
#include "objectMapGame.h"

class MyGame : public Core::Game{

private:
    bool game;
    int row;
    
    Adventure::Menu* gameMenu;
    
    //!Main menu.
    BackgroundShape *backgroundShape, *speechBox, *questionBox, *optionShape;

    Adventure::Dialog* mainMenu;
public:
    static int lastLoaded, loaded;
    static Debug::ScreenLog *sl;
    static BackgroundShape *bs;
    // State is changed by the Dialog
    static bool mainMenuMode;
    
    //Check if i already did cross with song.
    static bool oneCross;
    
    MyGame(int argc, char* argv[]);
    
    void initMainMenu();
    void initGameMenu();
    void setRelativePaths();
    
    
    void getParams(int argc, char* argv[]);
    void process();
    void render();
};
#endif /* defined(__Action_Adventure_Game_Engine__MyGame__) */
