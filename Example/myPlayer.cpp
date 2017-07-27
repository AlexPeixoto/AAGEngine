//
//  myPlayer.cpp
//  Game Engine
//
//  Created by Alex Peixoto on 11/19/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "myPlayer.h"

MyPlayer::MyPlayer(string idleSheet, int tileWidth, int tileHeight) : Player(idleSheet, tileWidth, tileHeight){
    fireballList=new vector<Fireball*>();
}

MyPlayer::~MyPlayer(){
    Player::~Player();
    if(fireballList!=nullptr){
        for(auto &fireball : *fireballList)
            delete fireball;
        delete fireballList;
        fireballList=nullptr;
    }
        
}

void MyPlayer::createFireball(){
    Fireball* f = new Fireball();
    f->image=new Image("fireball.png");
    f->direction=getFacing();
    f->killed=false;
    if(getFacing()==Directions::RIGHT)
        f->image->setPosition(Point2i(getPosition().x + 5, getPosition().y + 15));
    else if(getFacing()==Directions::LEFT)
        f->image->setPosition(Point2i(getPosition().x - 5, getPosition().y + 15));
    else if(getFacing()==Directions::UP)
        f->image->setPosition(Point2i(getPosition().x, getPosition().y + 5));
    else if(getFacing()==Directions::DOWN)
        f->image->setPosition(Point2i(getPosition().x, getPosition().y + 15));
    fireballList->push_back(f);
    
}
void MyPlayer::render(){
    Player::render();
    for(auto &fireball : *fireballList)
        if(!fireball->killed)
            fireball->image->render();
}

void MyPlayer::process(){
    Player::process();
    for(auto &fireball : *fireballList){
        if(fireball->killed)continue;
        if(fireball->direction==Directions::RIGHT)
            fireball->image->setPosition(Point2i(fireball->image->getPosition().x + 5, fireball->image->getPosition().y));
        else if(fireball->direction==Directions::LEFT)
            fireball->image->setPosition(Point2i(fireball->image->getPosition().x - 5, fireball->image->getPosition().y));
        else if(fireball->direction==Directions::UP)
            fireball->image->setPosition(Point2i(fireball->image->getPosition().x, fireball->image->getPosition().y - 5));
        else if(fireball->direction==Directions::DOWN)
            fireball->image->setPosition(Point2i(fireball->image->getPosition().x, fireball->image->getPosition().y + 5));
        if(fireball->image->getPosition().x > 1000 || fireball->image->getPosition().y > 1000 || fireball->image->getPosition().x < -100 || fireball->image->getPosition().x < -100){
            fireball->killed=true;
            delete fireball->image;
        }
    }
}

vector<MyPlayer::Fireball*>* MyPlayer::getFireballList(){
    return fireballList;
}