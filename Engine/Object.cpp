//
//  Object.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Object.h"

using namespace Adventure;

Object::Object(int id, string path, string name, int tileWidth, int tileHeight, bool randomize, bool load) : path(path), name(name), randomize(randomize){
    setTileSize(tileWidth, tileHeight);
    objectSprite=nullptr;
    properties=new map<string, string>();
    items=new map<int, int>();
    if(load)
        loadSprite();
    
}
Object::Object(int id, string path, string name, Vector2i tileSize, bool randomize, bool load){
    Object::Object(id, path, name, tileSize.x, tileSize.y, randomize, load);
}
Object::Object(){
    properties=new map<string, string>();
    items=new map<int, int>();
    objectSprite=nullptr;
}
Object::~Object(){
    if(objectSprite!=nullptr){
        delete objectSprite;
        objectSprite=nullptr;
    }
    if(properties!=nullptr){
        delete properties;
        properties=nullptr;
    }
}

void Object::render(){
    if(this->objectSprite==nullptr)
        if(!loadSprite())
            std::runtime_error("Error loading the sprite: " + path);
    objectSprite->render();
}

Sprite* Object::getSprite() const{
    return objectSprite;
}
bool Object::loadSprite(){
    if(objectSprite!=nullptr)
        return true;
    objectSprite=new Sprite(path, tileSize);
    if(objectSprite)
        return true;
    return false;
}
void Object::setName(string name){
    this->name=name;
}
void Object::setPath(string path, bool load){
    this->path=path;
    if(load){
        if(objectSprite!=nullptr){
            delete objectSprite;
            objectSprite=nullptr;
        }
        loadSprite();
    }
}
void Object::setPosition(int x, int y){
    position=Point2i(x, y);
    if(objectSprite!=nullptr)
        //Change position to Point2i
        objectSprite->setPosition(position);
}
void Object::setPosition(Point2i position){
    this->position=position;
    if(objectSprite)
        objectSprite->setPosition(position);
}
void Object::setTileSize(int tileWidth, int tileHeight){
    tileSize=Point2i(tileWidth, tileHeight);
    if(objectSprite)
        objectSprite->setTileSize(tileSize);
}
void Object::setTileSize(Vector2i tileSize){
    this->tileSize=tileSize;
}
void Object::setRandomize(bool randomize){
    this->randomize=randomize;
}
void Object::setRow(int row){
    tileIndex.y=row;
    if(objectSprite!=nullptr){
        objectSprite->setRow(row);
    }
}
void Object::setColumn(int column){
    tileIndex.x=column;
    if(objectSprite!=nullptr){
        objectSprite->setColumn(column);
    }
}
void Object::setTileIndex(Point2i tileIndex){
    this->tileIndex=tileIndex;
    if(objectSprite!=nullptr){
        objectSprite->setColumn(tileIndex.x);
        objectSprite->setRow(tileIndex.y);
    }
}
void Object::updateTileIndex(){
    if(objectSprite!=nullptr){
        objectSprite->setColumn(tileIndex.x);
        objectSprite->setRow(tileIndex.y);
    }
}

string Object::getName() const{
    return name;
}
string Object::getPath() const{
    return path;
}
Point2i Object::getPosition(){
    return position;
}
Vector2i Object::getTileSize(){
    return tileSize;
}
bool Object::getRandomize(){
    return randomize;
}
void Object::addProperty(string key, string value){
    if(properties==nullptr)
        properties=new map<string, string>();
    if(properties->find(key)!=properties->end())
        throw  runtime_error("[Object] Cannot add a duplicated key on the properties list");
    properties->insert(make_pair(key, value));
    
}
int Object::getId(){
    return this->id;
}
bool Object::updateProperty(string key, string value){
    try {
        properties->at(key)=value;
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}
//If the property dont exists the out of range exception must be intercepted by the function above in the stack
string Object::getProperty(string key){
    if(properties->find(key)==properties->end())
        throw  runtime_error("[Object] Cannot find the property with the specified key");
    return properties->at(key);
}
bool Object::removeProperty(string key){
    map<string, string>::const_iterator p;
    if(properties!=nullptr)
        for (auto& x: *properties) {
            if(x.first == key){
                properties->erase(p);
                return true;
            }
        }
    return false;
}

void Object::addItem(int id, int quantity){
    if(items==nullptr)
        items=new map<int, int>();
    if(items->find(id)!=items->end())
        throw  runtime_error("[Object] Cannot add a duplicated key on the items list");
    items->insert(make_pair(id, quantity));
}
bool Object::updateItem(int id, int quantity){
    try {
        items->at(id)=quantity;
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}
int Object::getItemQuantity(int id){
    if(items->find(id)==items->end())
        throw  runtime_error("[Object] Cannot find the item with the specified id");
    return items->at(id);
}
bool Object::removeItem(int id){
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
int Object::getRow(){
    return tileIndex.y;
}
int Object::getColumn(){
    return tileIndex.x;
}
Point2i Object::getTileIndex(){
    return tileIndex;
}
