//
//  MainLevel.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "testMap.h"
using Core::Collision;
using Core::Node;
using Core::Pathfind;
using Core::InputControl;

TestMap::TestMap(map<string, string> params):Level(){
    //Define de qual mapa foi carregado
    MyGame::loaded=2;
    //Inicializa estruturas
    p=new Adventure::Player("/Developer/movement.png", 32, 64);
    mapLevel="/Users/alexpeixoto/Documents/maps/testMap.map";
    collisionLevel="/Users/alexpeixoto/Documents/maps/testMap.map.collision";
    itemLevel="/Users/alexpeixoto/Documents/maps/testMap.map.item";
    soundLevel="/Users/alexpeixoto/Documents/maps/testMap.map.sound";
    objectLevel="/Users/alexpeixoto/Documents/maps/testMap.map.object";
    warpLevel="/Users/alexpeixoto/Documents/maps/testMap.map.warp";
    mapManager.loadTileLayer(mapLevel);
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/testMap.map.warpList");
    SoundEffectManager::unloadData();
    Point2f playerPosition;
    playerPosition.x = 360;
    playerPosition.y = 0;
    p->setPosition(playerPosition);
    p->setLoop(true);
    p->setPixelsPerCall(150);
    p->resetLoopTo(3);
    p->setWidthScale(1);
    p->setHeightScale(1);
    p->setChangeOnCall(20);
    p->setSpriteRow(4);
    p->setSpriteColumn(1);

    
    i1=new Core::Image("/Users/alexpeixoto/Desktop/b1.png");
    i2=new Core::Image("/Users/alexpeixoto/Desktop/b2.png");
    i1->setPosition(Point2i(300, 200));
    i2->setPosition(Point2i(400, 200));
    
    collided=false;
    
    _p=new Adventure::Character("/Developer/movement.png", 32, 64);
    _p->setPosition(Point2f(32, 32));
    _p->setChangeOnCall(20);
    _p->setLoop(true);
    _p->resetLoopTo(3);
    p->updateDirection(Adventure::Character::Directions::RIGHT, true);
    
    moveWithClearance();
    
    MyGame::bs->setPosition(MyGame::bs->getPosition().x, 350);
    MyGame::sl->setPosition(MyGame::sl->getPosition().x, 350);
        // Inicializa musicas
    //BackgroundMusic::loadSong("/Users/alexpeixoto/Downloads/AF/S0.ogg");
    //BackgroundMusic::play();
    //BackgroundMusic::intersectWith("/Users/alexpeixoto/Downloads/AF/S2.ogg", BackgroundMusic::IntersectMode::CROSS, 10);
}
TestMap::~TestMap(){
    MyGame::bs->setPosition(MyGame::bs->getPosition().x, 0);
    MyGame::sl->setPosition(MyGame::sl->getPosition().x, 0);
    delete p;
    WarpManager::unloadData();
}
void TestMap::moveWithClearance(){
    int *movementMap = new int[110];
    for(int x=0;x<110;x++)
            movementMap[x]=0;
    
    pf=new Pathfind();

    
    movementMap[3*10+0]=movementMap[3*10+1]=movementMap[3*10+2]=movementMap[3*10+3]=movementMap[3*10+4]=movementMap[3*10+6]=-1;
    movementMap[6*10+6]=movementMap[6*10+5]=-1;
    pf->initMatrix(Vector2i(10, 10), movementMap);
    pfBeginNode=pf->generatePathfind(Point2i(1, 1), Point2i(3, 6), 2);

    if(pfBeginNode!=nullptr)
        _p->moveWithNodes(pfBeginNode, mapManager.getMovementPointer(), Vector2i(60, 60), Vector2i(32, 32), 30);
   }
// Gerenciamento de movimento sem camera
void TestMap::movement(){
    Core::Collision::BoundingBox b;
    
    b.size.x=(float)this->p->getSprite()->getTileSize().x;
	b.size.y = (float)ceil(this->p->getSprite()->getTileSize().y / 2);
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
void TestMap::process(){
    Game::setDeltaTime();
    
    i2->setRotation(i2->getRotation()+15*Game::getDeltaTimef());
    
    Point2f a1[4];
    Point2f a2[4];
    Collision::getImageAxis(i1, a1);
    Collision::getImageAxis(i2, a2);
    //processa OBB
    if(Collision::collidedOBB(a1, a2) == true && collided==false){
        collided=true;
        LogManager::log(Debug::LogLevel::MESSAGE, "Collided.", "");
    }
    else if(Collision::collidedOBB(a1, a2) == false && collided==true){
        collided=false;
        LogManager::log(Debug::LogLevel::MESSAGE, "Didn't collided.", "");
    }
    
    movement();
	mapManager.process((float)p->getPosition().x, (float)p->getPosition().y, 0, 0);
}
// Renderiza personagem e elementos do mapa
void TestMap::render(){
    mapManager.render(0, 0, Game::window->getSize().x, Game::window->getSize().y);
    p->render();
    _p->render();
    i2->render();
    i1->render();
    MyGame::bs->render();
    MyGame::sl->render();
}