//
//  MainLevel.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__TestMap__
#define __Action_Adventure_Game_Engine__TestMap__
#include <iostream>
#include "Level.h"
#include "Game.h"
#include "Player.h"
#include "Image.h"
#include "MapManager.h"
#include "MyGame.h"

using namespace Adventure;
using namespace Core;
using namespace Debug;
class TestMap : public Level{
    
private:
    string mapLevel, collisionLevel, itemLevel, soundLevel, objectLevel, warpLevel;
    
    Player *p;
    Character *_p;
    MapManager mapManager;
    WarpManager *m;
    float deltaTime;
    
    Core::Image *i1, *i2;
    
    bool collided;
    
    
    Pathfind* pf;
    //player first begin node and player second begin node
    Node *pfBeginNode, *psBeginNode;

    
public:
    
    //Test propouses just initialize files
    TestMap(map<string, string> params);
    ~TestMap();
    void initData();
    
    void movement();
    void changeIndex();
    
    void moveWithClearance();
    
    void process();
    void render();
};

#endif /* defined(__Action_Adventure_Game_Engine__MainLevel__) */
