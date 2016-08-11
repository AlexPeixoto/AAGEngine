//
//  MainLevel.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "closedMap.h"
using Core::Collision;
using Core::Node;
using Core::Pathfind;
using Core::InputControl;

ClosedMap::ClosedMap(map<string, string> params):Level(){
    //Define de qual mapa foi carregado
    MyGame::loaded=1;
    //Inicializa estruturas
    p=new Adventure::Player("/Developer/movement.png", 32, 64);
    mapLevel="/Users/alexpeixoto/Documents/maps/houseClear.map";
    collisionLevel="/Users/alexpeixoto/Documents/maps/houseClear.map.collision";
    itemLevel="/Users/alexpeixoto/Documents/maps/houseClear.map.item";
    soundLevel="/Users/alexpeixoto/Documents/maps/houseClear.map.sound";
    objectLevel="/Users/alexpeixoto/Documents/maps/houseClear.map.object";
    warpLevel="/Users/alexpeixoto/Documents/maps/houseClear.map.warp";
    WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/houseClear.map.warpList");
    mapManager.loadTileLayer(mapLevel);
    mapManager.getTileLayer()->loadTileMap("/Users/alexpeixoto/Documents/maps/houseElements.map");
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/houseElements.map.warpList");
    SoundEffectManager::unloadData();
    Point2f playerPosition;
    playerPosition.x = 480;
    playerPosition.y = 100;
    p->setPosition(playerPosition);
    p->setLoop(true);
    p->setPixelsPerCall(150);
    p->resetLoopTo(3);
    p->setWidthScale(1);
    p->setHeightScale(1);
    p->setChangeOnCall(20);
    p->setSpriteRow(4);
    
    // Inicializa musicas
    //BackgroundMusic::loadSong("/Users/alexpeixoto/Downloads/AF/S0.ogg");
    //BackgroundMusic::play();
    //BackgroundMusic::intersectWith("/Users/alexpeixoto/Downloads/AF/S2.ogg", BackgroundMusic::IntersectMode::CROSS, 10);
}
ClosedMap::~ClosedMap(){
    delete p;
    WarpManager::unloadData();
}
// Gerenciamento de movimento sem camera
void ClosedMap::movement(){
    Core::Collision::BoundingBox b;
    
    b.size.x=this->p->getSprite()->getTileSize().x;
    b.size.y=ceil(this->p->getSprite()->getTileSize().y/2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::LShift, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(11, Core::InputControl::State::Held)){
        this->p->setPixelsPerCall(200);
        this->p->setChangeOnCall(10);
    }
    else{
        this->p->setChangeOnCall(15);
        this->p->setPixelsPerCall(150);
    }
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Right, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(5, Core::InputControl::State::Held)){
        //Check if the player can move
        //I need to get the float position from the player and add the movement to check if it is allowed
        b.position.x=this->p->getPosition().x+this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::RIGHT, true);
            this->p->setSpriteColumn(1);
            return;
        }
        //Move Player
        this->p->updateByKeyboard(Adventure::Character::Directions::RIGHT, Game::getDeltaTimef());
    }
    
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Left, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(7, Core::InputControl::State::Held)){
        b.position.x=this->p->getPosition().x-this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.x < 0){
            this->p->updateDirection(Adventure::Character::Directions::LEFT, true);
            this->p->setSpriteColumn(1);
            return;
        }
        this->p->updateByKeyboard(Adventure::Character::Directions::LEFT, Game::getDeltaTimef());
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Up, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y-this->p->getPixelsPerCall()*Game::getDeltaTimef()+b.size.y;
        
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.y < 0){
            this->p->updateDirection(Adventure::Character::Directions::UP, true);
            this->p->setSpriteColumn(1);
            return;
        }
        this->p->updateByKeyboard(Adventure::Character::Directions::UP, Game::getDeltaTimef());
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Down, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y+(this->p->getPixelsPerCall()*Game::getDeltaTimef())+b.size.y;
        
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::DOWN, true);
            this->p->setSpriteColumn(1);
            return;
        }
        this->p->updateByKeyboard(Adventure::Character::Directions::DOWN, Game::getDeltaTimef());
    }
}
// Processa movimento assim como a camera (colisão incluso)
void ClosedMap::process(){
    Game::setDeltaTime();
    
    movement();
    mapManager.process(p->getPosition().x, p->getPosition().y, 0, 0);
}
// Renderiza personagem e elementos do mapa
void ClosedMap::render(){
    mapManager.render(0, 0, Game::window->getSize().x, Game::window->getSize().y);
    p->render();
    MyGame::bs->render();
    MyGame::sl->render();
}