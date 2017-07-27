//
//  Object.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Object.h"

using namespace Adventure;

Object::Object(int id, const std::string& path, const std::string& name, int tileWidth, int tileHeight, bool randomize, bool load) : path(path), name(name), randomize(randomize){
    setTileSize(tileWidth, tileHeight);
    objectSprite=nullptr;
    properties=new std::map<std::string, std::string>();
    items=new std::map<int, int>();
    if(load)
        loadSprite();
    
}
Object::Object(int id, const std::string& path, const std::string& name, Vector2i tileSize, bool randomize, bool load){
    Object::Object(id, path, name, tileSize.x, tileSize.y, randomize, load);
}
Object::Object(){
    properties=new std::map<std::string, std::string>();
    items=new std::map<int, int>();
    objectSprite=nullptr;
}
Object::~Object(){
    delete objectSprite;
    delete properties;
	objectSprite = nullptr;
	properties = nullptr;
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
void Object::setName(const std::string& name){
    this->name=name;
}
void Object::setPath(const std::string& path, bool load){
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
Point2i Object::getPosition() const{
    return position;
}
Vector2i Object::getTileSize() const{
    return tileSize;
}
bool Object::getRandomize() const{
    return randomize;
}
void Object::addProperty(const std::string& key, const std::string& value){
    if(properties==nullptr)
        properties=new std::map<std::string, std::string>();
    if(properties->find(key)!=properties->end())
        throw  runtime_error("[Object] Cannot add a duplicated key on the properties list");
    properties->insert(make_pair(key, value));
    
}
int Object::getId() const{
    return this->id;
}
bool Object::updateProperty(const std::string& key, const std::string& value){
    try {
        properties->at(key)=value;
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}
//If the property dont exists the out of range exception must be intercepted by the function above in the stack
std::string Object::getProperty(const std::string& key) const{
    if(properties->find(key)==properties->end())
        throw  runtime_error("[Object] Cannot find the property with the specified key");
    return properties->at(key);
}
bool Object::removeProperty(const std::string& key){
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
int Object::getItemQuantity(int id) const{
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
int Object::getRow() const{
    return tileIndex.y;
}
int Object::getColumn() const{
    return tileIndex.x;
}
Point2i Object::getTileIndex() const{
    return tileIndex;
}
