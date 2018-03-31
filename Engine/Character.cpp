//
//  Prototype.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 2/12/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Character.h"

using namespace Adventure;

Character::Character(const std::string& idleSheet, int tileWidth, int tileHeight){
    idle=true;
    movement=false;
    index=0;
    
    spriteList = new vector<Sprite*>();
    spriteList->push_back(new Sprite(idleSheet, tileWidth, tileHeight));
    
    lastDirection=Directions::NONE;
    callsOnFrame=0;
    changeOnCall=0;
    pixelsPerCall=1;
    
    properties=nullptr;
    
    autoMovement=false;
}
Character::Character(const std::string& idleSheet, Vector2i tileSize){
    Character(idleSheet, tileSize.x, tileSize.y);
}
Character::~Character(){
    if(this->properties!=nullptr){
        delete this->properties;
        properties=nullptr;
    }
    if(spriteList!=nullptr){
#ifndef _WIN3
        for_each(spriteList->begin(), spriteList->end(), default_delete<Sprite>());
#else
for_each(spriteList->begin(), spriteList->end(),
	[](Sprite* s){
	delete s;
});
#endif
        delete spriteList;
        spriteList=nullptr;
    }
}
Character::Directions Character::getFacing(){
    return this->facing;
}

bool Character::loadMovementSheet(const string& path, int tileWidth, int tileHeight){
    if(!this->movement){
        this->spriteList->push_back(new Sprite(path, tileWidth, tileHeight));
        this->movement=true;
        return true;
    }
    return false;
}
bool Character::loadMovementSheet(const string& path, Vector2i tileSize){
    if(!this->movement){
        this->spriteList->push_back(new Sprite(path, tileSize.x, tileSize.y));
        this->movement=true;
        return true;
    }
    return false;
}
void Character::render(){
    if(this->spriteList->at(index)!=nullptr)this->spriteList->at(index)->render();
}
void Character::render(const Vector2i& movement){
    if(autoMovement){
        render();
        return;
    }
    if(this->spriteList->at(index)!=nullptr){
        Point2i position=(Point2i)this->position;
        Point2i finalPosition=position;
        finalPosition.x+=movement.x;
        finalPosition.y+=movement.y;
        // Update position
        this->spriteList->at(index)->setPosition(finalPosition);
        // Send to the framebuffer
        this->spriteList->at(index)->render();
        // Return to the original position
        this->spriteList->at(index)->setPosition(position);
    }
}
void Character::resetLoopTo(int index){
    this->spriteList->at(this->index)->resetLoopTo(index);
}
int Character::getPixelsPerCall(){
    return this->pixelsPerCall;
}
void Character::setPixelsPerCall(int pixelsPerCall){
    this->pixelsPerCall=pixelsPerCall;
}
void Character::setChangeOnCall(int changeOnCall){
    this->changeOnCall=changeOnCall;
}
void Character::setLoop(bool loop){
    this->spriteList->at(this->index)->setLoop(loop);
}
void Character::setHeightScale(int height){
    this->spriteList->at(this->index)->setHeightScale(height);
}
void Character::setWidthScale(int width){
    this->spriteList->at(this->index)->setWidthScale(width);
}
void Character::setSpriteColumn(int column){
    this->spriteList->at(index)->setColumn(column);
}
void Character::setSpriteRow(int row){
    this->spriteList->at(index)->setRow(row);
}
void Character::next(){
    this->spriteList->at(index)->next();
}
void Character::prev(){
    this->spriteList->at(index)->prev();
}
void Character::changeSprite(int index){
    this->index=index;
}
void Character::disableSprite(int index){
    //Cannot remove idle sprite
    if(index > 0){
        delete this->spriteList->at(index);
        this->spriteList->at(index)=nullptr;
    }
        
}
void Character::updateDirection(Character::Directions direction, bool updateY){
    if(this->facing==direction)return;
    this->facing=direction;
    //(direction==Down || direction==Left)*(abs(Left)+abs(Down)+2)
    if(updateY){
        this->setSpriteRow(abs((int)direction+1));
        this->callsOnFrame=0;
        this->lastDirection=direction;
        
    }
}
int Character::addSprite(const string& path, int tileWidth, int tileHeight){
    int size=(int)this->spriteList->size();
    
    this->spriteList->push_back(new Sprite(path, tileWidth, tileHeight));
    
    return this->spriteList->size() > size ? ((int)this->spriteList->size()-1) : -1;
}
int Character::addSprite(const string& path, Vector2i tileSize){
    int size=(int)this->spriteList->size();
    
    this->spriteList->push_back(new Sprite(path, tileSize.x, tileSize.y));
    
    return this->spriteList->size() > size ? ((int)this->spriteList->size()-1) : -1;
}
Point2f Character::getPosition(){
    return this->position;
}
void Character::addToPosition(const Vector2i& addPosition){
    if(++this->callsOnFrame>=this->changeOnCall){
         this->next();
         this->callsOnFrame=0;
    }
    this->position.x+=addPosition.x;
    this->position.y+=addPosition.y;
    Point2i position;
    position.x = this->position.x;
    position.y = this->position.y;
    
    this->spriteList->at(index)->setPosition(position);
}
void Character::call(){
    if(++this->callsOnFrame==this->changeOnCall){
        this->next();
        this->callsOnFrame=0;
    }
}
void Character::setPosition(const Point2f& newPosition){
    this->position=newPosition;
    Point2i position;
    position.x = this->position.x;
    position.y = this->position.y;
    this->spriteList->at(index)->setPosition(position);
}
bool Character::isAdjacent(const Point2i& p1, const Point2i& p2) const{
    return (p1.x+1 == p2.x && p1.y == p2.y) ||
           (p1.x == p2.x && p1.y+1 == p2.y) ||
           (p1.x-1 == p2.x && p1.y == p2.y) ||
           (p1.x == p2.x && p1.y-1 == p2.y);
}
Adventure::Character::Directions Character::getDirectionFromMovement(const Vector2f& movement){
    if(movement.x > 0)return Directions::RIGHT;
    if(movement.x < 0)return Directions::LEFT;
    if(movement.y > 0)return Directions::DOWN;
    if(movement.y < 0)return Directions::UP;

    return Directions::NONE;
}
void Character::moveWithNodes(Node* nodes, Vector2f* cameraMovement, const Vector2i& addMovimentPerSecond, const Vector2i& tileSize, float frameRate){
    thread th([=](){
        Directions oldDirection, newDirection;
        oldDirection=newDirection=Directions::NONE;
        autoMovement=true;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        long long elapsedMilliseconds=100;
        long long elapsedFrameMilliseconds=1;
        long long sleepMilliseconds=100;
        Node* destiny=nodes;
        if(destiny->getID().x==position.x/tileSize.x && destiny->getID().y==position.y/tileSize.y){
            if(destiny->getParent()==nullptr){
                autoMovement=false;
                return;
            }
            else{
                destiny=destiny->getParent();
            }
        }
        while(true){
            start = std::chrono::system_clock::now();
            if(!Character::isAdjacent(Point2i((int)(position.x/tileSize.x), (int)(position.y/tileSize.y)), destiny->getID())){
                autoMovement=false;
                setSpriteColumn(1);
                break;
            }

            /// Can be 1, -1 or 0
            // / tileSize because the destiny is a tile too
            Vector2f movementToAdd=Vector2f(destiny->getID().x-(int)position.x/tileSize.x, destiny->getID().y-(int)position.y/tileSize.y);
            position.x+=movementToAdd.x*((addMovimentPerSecond.x/frameRate));//*elapsedFrameMilliseconds/60.0f);
            position.y+=movementToAdd.y*((addMovimentPerSecond.y/frameRate));//*elapsedFrameMilliseconds/60.0f);
            //Check if i changed the direction
            oldDirection=newDirection;
            newDirection=getDirectionFromMovement(movementToAdd);
            if(oldDirection!=newDirection){
                Character::updateDirection(newDirection, true);
                callsOnFrame=0;
            }
            // Update Sprite movement
            if(++callsOnFrame>=changeOnCall){
                next();
                callsOnFrame=0;
            }
            
            //call();
            spriteList->at(index)->setPosition((Point2i)position+((Vector2i)*cameraMovement));
            if(abs((int)position.x/tileSize.x) == abs((int)destiny->getID().x) && abs((int)position.y/tileSize.y) == abs((int)destiny->getID().y)){
                if(destiny->getParent()==nullptr){
                    setSpriteColumn(1);
                    autoMovement=false;
                    break;
                }
                else{
                    destiny=destiny->getParent();
                }
            }
            end = std::chrono::system_clock::now();
            elapsedMilliseconds=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            sleepMilliseconds=(1000/frameRate-elapsedMilliseconds) > 0 ? 1000/frameRate : 1;
            this_thread::sleep_for(chrono::milliseconds(sleepMilliseconds));
            //calculate the movement
            end = std::chrono::system_clock::now();
            elapsedFrameMilliseconds=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        }
        //Stop auto movement render process
        setSpriteColumn(1);
        autoMovement=false;
    });
    th.detach();
}
int Character::getIndex(){
    return this->index;
}
Sprite* Character::getSprite() const{
    return this->spriteList->at(index);
}

std::map<std::string, std::string>::const_iterator Character::findProperty(const std::string& key) const{
    return this->properties->find(key);
}
void Character::addProperty(const std::string& key, const std::string& value){
    if(properties==nullptr)
        properties=new map<std::string, std::string>();
    properties->insert(make_pair(key, value));
    
}
void Character::updateProperty(const std::string& key, const std::string& value){
    std::map<std::string, std::string>::iterator it = properties->find(key);
    if(it == this->properties->end())
        this->properties->insert(make_pair(key, value));
    it->second=value;
}
string Character::getProperty(const std::string& key) const{
    map<string, string>::const_iterator it = findProperty(key);
    if(it==properties->end())
        throw runtime_error("[Prototype] Cannot find the property with the specified key");
    return it->second;
}
bool Character::removeProperty(const std::string& key){
    map<string, string>::const_iterator it = findProperty(key);
    if(it == properties->end())
        return false;
    properties->erase(it);
    return true;
}
void Character::addItem(int id, int quantity){
    if(items==nullptr)
        items=new map<int, int>();
    if(items->find(id)!=items->end())
        throw  runtime_error("[Prototype] Cannot add a duplicated key on the items list");
    items->insert(make_pair(id, quantity));
}
bool Character::updateItem(int id, int quantity){
    try {
        items->at(id)=quantity;
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}
int Character::getItemQuantity(int id) const{
    if(items->find(id)==items->end())
        throw  runtime_error("[Prototype] Cannot find the item with the specified id");
    return items->at(id);
}
bool Character::removeItem(int id){
    map<int, int>::const_iterator p;
    if(items!=nullptr)
        for (auto& x: *items) {
            if(x.first == id){
                items->erase(p);
                return true;
            }
        }
    return false;
}
bool Character::getAutoMovement() const{
    return autoMovement;
}