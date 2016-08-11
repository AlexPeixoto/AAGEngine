//
//  MainLevel.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "objectMapGame.h"
using Core::Collision;
using Core::Node;
using Core::Pathfind;
using Core::InputControl;

ObjectMapGame::ObjectMapGame():Level(){
    //Define de qual mapa foi carregado
    MyGame::loaded=3;
    p=new MyPlayer("/Developer/movement.png", 32, 64);
    p->setPosition(Point2f(40, 100));
    p->setLoop(true);
    p->setPixelsPerCall(150);
    p->resetLoopTo(3);
    p->setWidthScale(1);
    p->setHeightScale(1);
    p->setChangeOnCall(20);

    d=new Dialog("/Developer/times.ttf");
    mapLevel="/Users/alexpeixoto/Desktop/objectMap.map";
    collisionLevel="/Users/alexpeixoto/Desktop/objectMap.map.collision";
    itemLevel="/Users/alexpeixoto/Desktop/objectMap.map.item";
    soundLevel="/Users/alexpeixoto/Desktop/objectMap.map.sound";
    objectLevel="/Users/alexpeixoto/Desktop/objectMap.map.object";
    warpLevel="/Users/alexpeixoto/Desktop/objectMap.map.warp";
    mapManager.loadTileLayer(mapLevel);
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    ObjectManager::loadFromFile("/Users/alexpeixoto/Desktop/objectMap.map.objectList");
    SoundEffectManager::unloadData();
    
    LogManager::log(Debug::LogLevel::MESSAGE, "Exit closed.", "");
    
    isOpen=false;
    MyGame::bs->setPosition(MyGame::bs->getPosition().x, 350);
    MyGame::sl->setPosition(MyGame::sl->getPosition().x, 350);
    
    acidList=new vector<Acid*>();
    for(int y=10; y<180; y+=20){
        Acid* acd = new Acid;
        acd->acid=new Core::Image("acid.png");
        acd->position.x=200;
        acd->position.y=y;
        acd->killed=false;
        acidList->push_back(acd);
    }
    
    //init acid sound
    
    sb = new SoundBuffer();
    s = new Sound();
    if(sb->loadFromFile("./sounds/acid.wav"))
        s->setBuffer(*sb);
}

ObjectMapGame::ObjectMapGame(map<string, string> params):ObjectMapGame(){
}
ObjectMapGame::~ObjectMapGame(){
    delete p;
    delete d;
    ObjectManager::unloadData();
    WarpManager::unloadData();
    MyGame::bs->setPosition(MyGame::bs->getPosition().x, 0);
    MyGame::sl->setPosition(MyGame::sl->getPosition().x, 0);
}
void ObjectMapGame::getItem(){
    //Player bounding box and item bounding box
    Core::Collision::BoundingBox b, ibb;
    
    
	b.size.x = (float)this->p->getSprite()->getTileSize().x;
	b.size.y = (float)ceil(this->p->getSprite()->getTileSize().y / 2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    //get an
    b.position-=(Point2f)mapManager.getMovement();
    auto* itemList=mapManager.getItemMap()->getItemList();
    for(int x=0; x<itemList->size(); x++){
        ibb=mapManager.getItemMap()->getBoundingBox(itemList->at(x));
        if(Collision::collidedAABB(ibb, b)){
            LogManager::log(Debug::LogLevel::MESSAGE, "Item acquired.", "");
            itemList->erase(itemList->begin()+x);
            x=0;
        }
    }
}
void ObjectMapGame::movement(){
    Core::Collision::BoundingBox b;
    
	b.size.x = (float)this->p->getSprite()->getTileSize().x;
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
void ObjectMapGame::openObject(){
    if(isOpen)return;
    int threshhold=10;
    Core::Collision::BoundingBox b;
    
	b.size.x = (float)this->p->getSprite()->getTileSize().x;
	b.size.y = (float)ceil(this->p->getSprite()->getTileSize().y / 2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    int index;
    //verifica 4 colisões com a caixa
    if(p->getFacing()==Character::Directions::UP){
        b.position.y-=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            isOpen=true;
            WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/objectMap.map.warpList");
            LogManager::log(Debug::LogLevel::MESSAGE, "Exit is open.", "");
            mapManager.getObjectMap()->setSpriteIndex(index, 2, 1);
        }
    }
    if(p->getFacing()==Character::Directions::DOWN){
        b.position.y+=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            isOpen=true;
            WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/objectMap.map.warpList");
            LogManager::log(Debug::LogLevel::MESSAGE, "Exit is open.", "");
            mapManager.getObjectMap()->setSpriteIndex(index, 2, 1);
        }
    }
    if(p->getFacing()==Character::Directions::LEFT){
        b.position.x-=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            isOpen=true;
            WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/objectMap.map.warpList");
            LogManager::log(Debug::LogLevel::MESSAGE, "Exit is open.", "");
            mapManager.getObjectMap()->setSpriteIndex(index, 2, 1);
        }
    }
    if(p->getFacing()==Character::Directions::RIGHT){
        b.position.x+=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            isOpen=true;
            WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/objectMap.map.warpList");
            LogManager::log(Debug::LogLevel::MESSAGE, "Exit is open.", "");
            mapManager.getObjectMap()->setSpriteIndex(index, 2, 1);
        }
    }
}
void ObjectMapGame::collidedAcid(){
    for(auto it2=acidList->begin(); it2!=acidList->end(); it2++){
        if((*it2)->killed)continue;
        Collision::BoundingBox b1, b2;
        b1.position.x=p->getPosition().x;
        b1.position.y=p->getPosition().y;
		b1.size.x = (float)p->getSprite()->getTileSize().x;
		b1.size.y = (float)p->getSprite()->getTileSize().y;
        
		b2.position.x = (float)(*it2)->acid->getPosition().x;
		b2.position.y = (float)(*it2)->acid->getPosition().y;
		b2.size.x = (float)(*it2)->acid->getWidth();
		b2.size.y = (float)(*it2)->acid->getHeight();
        
        if(Collision::collidedAABB(b1, b2) == true){
            if(s->getStatus()==s->Stopped)
                s->play();
            //LogManager::log(Debug::LogLevel::MESSAGE, "Recebeu Dano, causado pelo acido!.", "");
            if(p->getFacing()==MyPlayer::Directions::RIGHT){
                p->addToPosition(Vector2i(-20, 0));
                break;
            }
            else if(p->getFacing()==MyPlayer::Directions::LEFT){
                p->addToPosition(Vector2i(20, 0));
                break;
            }
            else if(p->getFacing()==MyPlayer::Directions::UP){
                p->addToPosition(Vector2i(0, 20));
                break;
            }
            else if(p->getFacing()==MyPlayer::Directions::DOWN){
                p->addToPosition(Vector2i(0, -20));
                break;
            }
        }
    }

}
void ObjectMapGame::process(){
    Game::setDeltaTime();
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Return, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(14, Core::InputControl::State::Released))
        openObject();
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Space, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(15, Core::InputControl::State::Released))
        p->createFireball();
    
    
    for(auto it=p->getFireballList()->begin(); it!=p->getFireballList()->end(); it++){
        if((*it)->killed)continue;
        bool destroyMe=false;
        for(auto it2=acidList->begin(); it2!=acidList->end(); it2++){
            if((*it2)->killed)continue;
            Collision::BoundingBox b1, b2;
			b1.position.x = (float)(*it)->image->getPosition().x;
			b1.position.y = (float)(*it)->image->getPosition().y;
			b1.size.x = (float)(*it)->image->getWidth();
			b1.size.y = (float)(*it)->image->getHeight();
            
			b2.position.x = (float)(*it2)->acid->getPosition().x;
			b2.position.y = (float)(*it2)->acid->getPosition().y;
			b2.size.x = (float)(*it2)->acid->getWidth();
			b2.size.y = (float)(*it2)->acid->getHeight();
            
            if(Collision::collidedAABB(b1, b2) == true){
                (*it2)->killed=true;
                destroyMe=true;
            }
        }
        if(!(*it)->killed)
            (*it)->killed=destroyMe;
    }
    
    getItem();
    movement();
    collidedAcid();
	mapManager.process((float)p->getPosition().x, (float)p->getPosition().y, 0, 0);
    p->process();
    

}
void ObjectMapGame::render(){
    mapManager.render(0, 0, Game::window->getSize().x, Game::window->getSize().y);
    for(auto it=acidList->begin(); it!=acidList->end(); it++){
        if((*it)->killed==false){
            //manual camera movement
			(*it)->acid->setPosition(Point2i((int)((*it)->position.x + mapManager.getMovement().x), (int)((*it)->position.y + mapManager.getMovement().y)));
            (*it)->acid->render();
        }
    }
    p->render();
    MyGame::bs->render();
    MyGame::sl->render();
    
}