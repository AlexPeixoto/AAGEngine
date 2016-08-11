//
//  MainLevel.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__BeginMap__
#define __Action_Adventure_Game_Engine__BeginMap__

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
class BeginMap : public Level{
    
private:
    string mapLevel, collisionLevel, itemLevel, soundLevel, objectLevel, warpLevel;
    
    Player* p;
    Character* _p;
    MapManager mapManager;
    TextControl* t;
    SoundMap* sm;
    BackgroundShape *bs, *speechBox, *questionBox, *optionShape;
    Dialog* d;
    WarpManager *m;
    Menu* _m;
    
    Pathfind* pf;
    //player first begin node and player second begin node
    Node *pfBeginNode, *psBeginNode;
    
    bool isthread;
    int textIndex;
    
    float deltaTime;
    
    string message;
    bool messagePending;
    
    static bool renderText;
    static int mode;
    static bool stopScript;
    static bool autoBlock;
    
public:
    
    //Test propouses just initialize files
    BeginMap(map<string, string> params);
    ~BeginMap();
    void initData();
    
    void generatePathForPlayer(int mode=0);
    
    void movement();
    void changeIndex();
    
    void process();
    void render();
    
};

#endif /* defined(__Action_Adventure_Game_Engine__MainLevel__) */
