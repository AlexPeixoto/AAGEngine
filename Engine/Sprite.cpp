//
//  Sprite.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 1/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include <iostream>
#include "Sprite.h"

using namespace Core;
using namespace Adventure;
using namespace std;

Sprite::Sprite(string path, int tileWidth, int tileHeight) : Image(path){
    tileSize.x=tileWidth;
    tileSize.y=tileHeight;
    setTileSize((float)tileWidth, (float)tileHeight);
    index.x=index.y=1;
    reloading=false;
}
Sprite::Sprite(string path, Vector2i tileSize) : Image(path){
    setTileSize(tileSize);
    index.x=index.y=1;
    reloading=false;
}
Sprite::~Sprite(){
}
void Sprite::setTileSize(Vector2i tileSize){
    this->tileSize=tileSize;
}
void Sprite::setLoop(bool loop){
    this->loopToBegin=loop;
}
void Sprite::resetLoopTo(int index){
    this->loopTo=index;
}
void Sprite::setTileSize(float width, float height){
    tileSize.x=width;
    tileSize.y=height;
}
//To prevent some calculations store the limits when i load the image
void Sprite::next(){
    if(textureSize.x/((tileSize.x*(index.x+1))) >=1)index.x++;
    else if(loopToBegin)index.x=loopTo;
}
void Sprite::prev(){
    if(index.x>0)index.x--;
    
}
void Sprite::nextRow(){
    if(textureSize.y/((textureSize.y*(index.y+1))) >=1)index.x++;
}
void Sprite::prevRow(){
    if(index.y>0)index.x--;
}

void Sprite::setColumn(int column){
    if(textureSize.x/((float)(textureSize.x*(column+1))) >=0 && column>0)index.x=column;
}

void Sprite::setRow(int row){
    if((int)textureSize.y/(((int)textureSize.y*(row+1))) >=0 && row>0){
        index.y=row;
    }
}

void Sprite::changeSprite(const std::string& path, int tileWidth, int tileHeight){
    this->tileSize.x=tileWidth;
    this->tileSize.y=tileHeight;
    setTileSize(tileWidth, tileHeight);
    this->changeImage(path);
}
void Sprite::render(){
    if(reloading)return;
    this->renderSub((index.x-1)*tileSize.x, (index.y-1)*tileSize.y, tileSize.x, tileSize.y);
}
Point2i Sprite::getSpriteIndex() const{
    Point2i position;
    position.x=index.x;
    position.y=index.y;
    return position;
}
Vector2i Sprite::getTileSize() const{
    return tileSize;
}