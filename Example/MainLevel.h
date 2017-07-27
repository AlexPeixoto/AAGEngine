//
//  MainLevel.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__MainLevel__
#define __Action_Adventure_Game_Engine__MainLevel__

#include <iostream>
#include "Level.h"
#include "Game.h"
#include "Player.h"
#include "MapManager.h"
#include "TextControl.h"
#include "BackgroundMusic.h"
#include "SoundEffectManager.h"
#include "SoundMap.h"
#include "ScreenLog.h"
#include "BackgroundShape.h"
#include "Dialog.h"
#include "ObjectManager.h"
#include "Pathfind.h"
#include "Node.h"
#include "InputControl.h"
#include "TextTable.h"
#include "Menu.h"
#include "MyGame.h"


using namespace Adventure;
using namespace Core;
using namespace Debug;
class MainLevel : public Level{
    
private:
    string mapLevel, collisionLevel, itemLevel, soundLevel, objectLevel, warpLevel;
    
    bool spaceIsPressed, cIsPressed, returnIsPressed;
    
    Adventure::Sprite* img;
    Player* p;
    Character* _p;
    MapManager mapManager;
    TextControl* t;
    SoundMap* sm;
    ScreenLog* sl;
    BackgroundShape *bs, *speechBox, *questionBox, *optionShape;
    Dialog* d;
    WarpManager *m;
    Menu* _m;
    
    Core::Image *i1, *i2;
    
    Pathfind* pf;
    Node* pfBeginNode;
    
    bool isthread;
    int textIndex;
    
    float deltaTime;
    
	std::string message;
    bool messagePending;
    bool renderText;
    
    
public:
    //Test propouses just initialize files
    MainLevel();
    MainLevel(std::map<std::string, std::string> params);
    void initData();
    
    void generatePathForPlayer();
    
    void movement();
    void changeIndex();
    void getItem();
    void showMessage();
    void openObject();
    
    void process();
    void render();
    
};

#endif /* defined(__Action_Adventure_Game_Engine__MainLevel__) */
