//
//  WarpMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "WarpMap.h"
#include "LevelManager.h"
#include "Game.h"

using namespace Adventure;

std::string WarpMap::relativePath="";

WarpMap::WarpMap(){
    warpList=new vector<WarpFake*>();
}
WarpMap::WarpMap(string path){
    warpList=new vector<WarpFake*>();
    int size;
    std::string loadPath;
    if(relativePath.size()>0){
        size_t lastIndex=path.find_last_of("/");
        if(lastIndex!=string::npos)
            //if path have the / on the end
            loadPath=path[path.size()-1]=='/' ? relativePath+path.substr(lastIndex+1) : relativePath+"/"+path.substr(lastIndex+1);
        else
            loadPath=path[path.size()-1]=='/' ? relativePath+path : relativePath+"/"+path;
    }
    else
        loadPath=path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
    
    FILE* f = fopen(loadPath.c_str(), "rb");
    if(!f)
        throw std::runtime_error("[Warp Map] Impossible to load file: " + path);
    fread(&size, sizeof(int), 1, f);
    for(int x=0; x<size; x++){
        WarpFake *w=new WarpFake;
        fread(&w->id, sizeof(int), 1, f);
        fread(&w->position, sizeof(Point2i), 1, f);
        w->enabled=true;
        warpList->push_back(w);
    }
    fclose(f);
}

WarpMap::~WarpMap(){
    
}
void WarpMap::addWarp(int id, int x, int y, bool enabled){
    addWarp(id, Point2i(x, y), enabled);
}
void WarpMap::addWarp(int id, Point2i position, bool enabled){
    WarpFake* w=new WarpFake;
    w->id=id;
    w->position=position;
    w->enabled=enabled;
    warpList->push_back(w);
}
void WarpMap::removeWarp(size_t index){
    if(index < warpList->size()){
        delete warpList->at(index);
        warpList->at(index)=nullptr;
    }
}

std::vector<WarpMap::WarpFake*>* WarpMap::getWarpList() const{
    return warpList;
}

Core::Collision::BoundingBox WarpMap::getBoundingBox(WarpFake* w){
    Core::Collision::BoundingBox b;
    Warp* _w= WarpManager::getWarp(w->id);
    b.position=Point2f(static_cast<int>(w->position.x), static_cast<int>(w->position.y));
    b.size=(Vector2f)_w->getSize();
    return b;
}
void WarpMap::warpProcessCollision(Core::Collision::BoundingBox b, Vector2f movement, int* changeTo){
    Core::Collision::BoundingBox w;
    Warp* _warp=nullptr;
        for(auto &warp : *warpList){
            w.position=(Point2f)warp->position + movement;
            _warp=WarpManager::getWarp(warp->id);
            if(_warp==nullptr)
                continue;
            w.size=(Vector2f)_warp->getSize();
        
            if(Collision::collidedAABB(b, w))
                (*changeTo)=warp->id;
    }
    
}