//
//  MainLevel.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__ClosedMap__
#define __Action_Adventure_Game_Engine__ClosedMap__
#include <iostream>
#include "Level.h"
#include "Game.h"
#include "Player.h"
#include "MapManager.h"
#include "MyGame.h"

using namespace Adventure;
using namespace Core;
using namespace Debug;

class ClosedMap : public Level{
    
private:
    std::string mapLevel, collisionLevel, itemLevel, soundLevel, objectLevel, warpLevel;
    
    Player* p;
    MapManager mapManager;
    WarpManager *m;
    float deltaTime;
    
public:
    
    //Test propouses just initialize files
    ClosedMap(map<std::string, std::string> params);
    ~ClosedMap();
    void initData();
    
    void movement();
    void changeIndex();
    
    void process();
    void render();
};

#endif /* defined(__Action_Adventure_Game_Engine__MainLevel__) */
