//
//  Item.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Item.h"
using namespace Adventure;

Item::Item(int id, string path, string name, int tileWidth, int tileHeight, bool load) : path(path), name(name){
    setTileSize(tileWidth, tileHeight);
    itemSprite=nullptr;
    properties=new map<string, string>();
    if(load)
        loadSprite();
    
}
Item::Item(int id, string path, string name, Vector2i tileSize, bool load){
    Item::Item(id, path, name, tileSize.x, tileSize.y, load);
}
Item::Item(){
    properties=new map<string, string>();
    itemSprite=nullptr;
}
Item::~Item(){
    if(itemSprite!=nullptr){
        delete itemSprite;
        itemSprite=nullptr;
    }
    if(properties!=nullptr){
        delete properties;
        properties=nullptr;
    }
}

void Item::render(){
    if(this->itemSprite==nullptr)
        if(!loadSprite())
            cerr << "Error loading the sprite" << endl;
    itemSprite->render();
}

Sprite* Item::returnSprite() const{
    return itemSprite;
}
bool Item::loadSprite(){
    if(itemSprite!=nullptr)
        return true;
    itemSprite=new Sprite(path, tileSize);
    if(itemSprite)
        return true;
    return false;
}
void Item::setName(string name){
    this->name=name;
}
void Item::setPath(string path, bool load){
    this->path=path;
    if(load){
        if(itemSprite!=nullptr){
            delete itemSprite;
            itemSprite=nullptr;
        }
        loadSprite();
    }
}
void Item::setPosition(int x, int y){
    position=Point2i(x, y);
    if(itemSprite!=nullptr)
        //Change position to Point2i
        itemSprite->setPosition(position);
}
void Item::setPosition(Point2i position){
    this->position=position;
    if(itemSprite)
        itemSprite->setPosition(position);
}
void Item::setTileSize(int tileWidth, int tileHeight){
    tileSize=Point2i(tileWidth, tileHeight);
    if(itemSprite)
        itemSprite->setTileSize(tileSize);
}
void Item::setTileSize(Vector2i tileSize){
    this->tileSize=tileSize;
}
void Item::setRow(int row){
    tileIndex.y=row;
    if(itemSprite!=nullptr){
        itemSprite->setRow(row);
    }
}
void Item::setColumn(int column){
    tileIndex.x=column;
    if(itemSprite!=nullptr){
        itemSprite->setColumn(column);
    }
}
void Item::setTileIndex(Point2i tileIndex){
    this->tileIndex=tileIndex;
    if(itemSprite!=nullptr){
        itemSprite->setColumn(tileIndex.x);
        itemSprite->setRow(tileIndex.y);
    }
}
void Item::updateTileIndex(){
    if(itemSprite!=nullptr){
        itemSprite->setColumn(tileIndex.x);
        itemSprite->setRow(tileIndex.y);
    }
}

string Item::getName() const{
    return name;
}
string Item::getPath() const{
    return path;
}
Point2i Item::getPosition(){
    return position;
}
Vector2i Item::getTileSize(){
    return tileSize;
}
int Item::getRow(){
    return tileIndex.y;
}
int Item::getColumn(){
    return tileIndex.x;
}
Point2i Item::getTileIndex(){
    return tileIndex;
}
void Item::addProperty(string key, string value){
    if(properties==nullptr)
        properties=new map<string, string>();
    properties->insert(make_pair(key, value));
    
}
int Item::getId(){
    return this->id;
}
bool Item::updateProperty(string key, string value){
    try {
        properties->at(key)=value;
        return true;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}
//If the property dont exists the out of range exception must be intercepted by the function above in the stack
string Item::getProperty(string key){
    return properties->at(key);
}
bool Item::removeProperty(string key){
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
