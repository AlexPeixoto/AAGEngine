//
//  myPlayer.h
//  Game Engine
//
//  Created by Alex Peixoto on 11/19/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Game_Engine__myPlayer__
#define __Game_Engine__myPlayer__
#include "Player.h"
#include "Sprite.h"
#include "Image.h"
using namespace Adventure;
using Core::Image;

class MyPlayer : public Player{
private:
    typedef struct Fireball{
        Core::Image* image;
        Directions direction;
        bool killed;
    } Fireball;
    
    vector<Fireball*> *fireballList;
public:
    

    MyPlayer(string idleSheet, int tileWidth, int tileHeight);
    ~MyPlayer();
    
    
    void createFireball();
    
    void render();
    void process();
    
    vector<Fireball*>* getFireballList();
    
};

#endif /* defined(__Game_Engine__myPlayer__) */
