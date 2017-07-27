//
//  Map.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 1/20/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "TileLayer.h"
using namespace Adventure;

TileLayer::TileLayer(){
    tileList = new vector<TileMap*>();
}
TileLayer::TileLayer(string path){
    tileList = new vector<TileMap*>();
    loadTileMap(path);
}
TileLayer::~TileLayer(){
    if(tileList!=nullptr){
#ifndef _WIN32
        for_each(tileList->begin(), tileList->end(), default_delete<TileMap>());
#else
for_each(tileList->begin(), tileList->end(),
	[](TileMap* tm){
	delete tm;
});
#endif
        delete tileList;
        tileList=nullptr;
    }
}
void TileLayer::loadTileMap(string path){
    tileList->push_back(new TileMap(path));
}
bool TileLayer::isEnd(int x, int y, int width, int height){
    for(const auto& tile : *tileList)
        if(tile->getSize().x > x + width && tile->getSize().y > y + height)
            return true;
    return false;
}
bool TileLayer::isEnd(Core::Collision::BoundingBox b){
    return isEnd(b.position.x, b.position.y, b.size.x, b.size.y);
    
}
void TileLayer::render(Point2i position, Vector2i size, int index){
    this->render(position.x, position.y, size.x, size.y, index);
}
void TileLayer::render(int x, int y, int width, int height, int index)
{
    if(index==-1)
        for(const auto& tile : *tileList)
            tile->render(x, y, width, height);
    else
        tileList->at(index)->render(x, y, width, height);
}
void TileLayer::renderPerfect(Point2i position, Vector2i size, Vector2i movement, int index){
    this->renderPerfect(position.x, position.y, size.x, size.y, movement.x, movement.y, index);
}
void TileLayer::renderPerfect(int x, int y, int width, int height, int moveX, int moveY, int index){
    if(index==-1)
        for(const auto& tile : *tileList)
            tile->renderPerfect(x, y, width, height, moveX, moveY);
    else
        tileList->at(index)->render(x, y, width, height);
}
TileMap* TileLayer::getTileMap(int index){
    return tileList->at(index);
}