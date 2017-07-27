//
//  MapManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 3/7/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "MapManager.h"

using namespace Adventure;

MapManager::MapManager(){
    tl=nullptr;
    im=nullptr;
    sm=nullptr;
    om=nullptr;
    wm=nullptr;
    movement.x=movement.y=0;
}
MapManager::~MapManager(){
    if(tl!=nullptr)
        delete tl;
    if(im!=nullptr)
        delete im;
    if(sm!=nullptr)
        delete sm;
    if(om!=nullptr)
        delete om;
}
bool MapManager::loadTileLayer(string mapFile){
    tl=new TileLayer();
    if(!tl)return false;
    tl->loadTileMap(mapFile);
    return true;
}
bool MapManager::loadCollisionMap(string collisionFile){
    cm=new CollisionMap(collisionFile);
    if(!cm)return false;
    return true;
}
bool MapManager::loadItemMap(string itemFile) {
    im=new ItemMap(itemFile);
    if(!im)return false;
    return true;
}
bool MapManager::loadSoundMap(string soundFile){
    sm=new SoundMap(soundFile);
    if(!sm)return false;
    sm->updatePosition(sf::Point2i(0, 0));
    return true;
}
bool MapManager::loadObjectMap(string objectFile){
    om=new ObjectMap(objectFile);
    if(!om)return false;
    return true;
}
bool MapManager::loadWarpMap(string warpFile){
    wm=new WarpMap(warpFile);
    if(!wm)return false;
    return true;
}
void MapManager::move(float x, float y){
    movement.x+=x;
    movement.y+=y;
}
bool MapManager::isEnd(int x, int y, int width, int height){
    return tl->isEnd(x, y, width, height);
}
void MapManager::render(int x, int y, int width, int height)
{
    if(tl!=nullptr)
        tl->renderPerfect(Point2i(x, y), Vector2i(width, height), Vector2i(movement.x, movement.y));
    if(im!=nullptr)
        im->renderPerfect(Point2i(x, y), Vector2i(width, height), Vector2i(movement.x, movement.y));
    if(om!=nullptr)
        om->renderPerfect(Point2i(x, y), Vector2i(width, height), Vector2i(movement.x, movement.y));
}
bool MapManager::collided(Core::Collision::BoundingBox b){
    if(wm!=nullptr)
        wm->warpProcessCollision(b, movement, &LevelManager::changeTo);
    return (cm!=nullptr && cm->collided(b, movement)) || (om!=nullptr && om->collided(b, movement));
}
void MapManager::process(int x, int y, int height, int width){
    if(sm!=nullptr)
        sm->updatePosition(Point2i(x-movement.x, y-movement.y));
}
void MapManager::setTileLayer(TileLayer* tl){
    this->tl=tl;
}
void MapManager::setCollisionMap(CollisionMap* cm){
    this->cm=cm;
}
void MapManager::setItemMap(ItemMap* im){
    this->im=im;
}
void MapManager::setSoundMap(SoundMap* sm){
    this->sm=sm;
}
void MapManager::setObjectMap(ObjectMap* om){
    this->om=om;
}
void MapManager::setWarpMap(WarpMap* wm){
    this->wm=wm;
}
Vector2f MapManager::getMovement(){
    return movement;
}
Vector2f* MapManager::getMovementPointer(){
    return &movement;
}
TileLayer* MapManager::getTileLayer(){
    return tl;
}
CollisionMap* MapManager::getCollisionMap(){
    return cm;
}
ItemMap* MapManager::getItemMap(){
    return im;
}
SoundMap* MapManager::getSoundMap(){
    return sm;
}
ObjectMap* MapManager::getObjectMap(){
    return om;
}
WarpMap* MapManager::getWarptMap(){
    return wm;
}