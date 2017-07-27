//
//  Player.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 2/12/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

/*
 * This is a custom implementation of the Character, it is intended to the developer to implement its own player.
 */
#include "Player.h"

using namespace Adventure;

Player::Player(const std::string& idleSheet, int tileWidth, int tileHeight):Character(idleSheet, tileWidth, tileHeight){}
Player::Player(const std::string& idleSheet, Vector2i tileSize) :Character(idleSheet, tileSize){}
Player::~Player(){}
void Player::process(){}
void Player::render(){
    Character::render();
}

void Player::updateByKeyboard(Directions direction, float deltaTime){
    //FACE DESIGNED DIRECTION
    Character::updateDirection(direction, true);
    Vector2i destiny;
    if(direction == Directions::RIGHT || direction == Directions::LEFT)
        destiny.x=((int)direction-4) + /*if is right, force 1 and not 0 */ ( 1 * (direction == Directions::RIGHT) );
    else
        destiny.y-=((int)direction-2)+ /*if is up, force 1 and not 0 */ ( 1 * (direction == Directions::UP) );
    destiny.x*=(this->pixelsPerCall*deltaTime);//*Core::Game::getDeltaTimef());
    destiny.y*=(this->pixelsPerCall*deltaTime);
    walkTo(destiny);
    
}
void Player::walkTo(Vector2i movement){
    addToPosition(movement);
}
