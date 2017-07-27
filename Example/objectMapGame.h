//
//  MainLevel.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__objectMapGame__
#define __Action_Adventure_Game_Engine__objectMapGame__
#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include "Level.h"
#include "MyGame.h"
#include "myPlayer.h"
#include "MapManager.h"
#include "Collision.h"
#include "InputControl.h"

using namespace Adventure;
using namespace Core;
using namespace Debug;
class ObjectMapGame : public Level{
    
private:
    typedef struct Acid{
        Core::Image* acid;
        Point2i position;
        bool killed;
    } Acid;
    
    vector<Acid*> *acidList;
    string mapLevel, collisionLevel, itemLevel, soundLevel, objectLevel, warpLevel;

    MyPlayer* p;
    MapManager mapManager;
    Dialog* d;
    WarpManager *m;
    float deltaTime;
    
    bool isOpen;
    //Acid sound
    SoundBuffer* sb;
    Sound* s;

public:
    //Test propouses just initialize files
    ObjectMapGame();
    ObjectMapGame(map<string, string> params);
    ~ObjectMapGame();
    void generatePathForPlayer();
    
    void movement();
    void changeIndex();
    void getItem();
    void openObject();
    
    void process();
    void render();
 
    
    void collidedAcid();
    void playSamage();
    
};

#endif /* defined(__Action_Adventure_Game_Engine__MainLevel__) */
