//
//  WarpManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "WarpManager.h"

using namespace Adventure;
vector<Warp*> *WarpManager::warpList=new vector<Warp*>();
string WarpManager::relativePath="";

WarpManager::~WarpManager(){
    if(warpList!=nullptr){
#ifndef _WIN32
		for_each(warpList->begin(), warpList->end(), default_delete<Warp>());
#else
		for_each(warpList->begin(), warpList->end(),
			[](Warp* w){
			delete w;
		});
#endif
        delete warpList;
        warpList=nullptr;
    }
}

Warp* WarpManager::getWarp(int id){
    for(const auto& warp : *warpList)
        if(warp->id == id)
            return warp;
    return nullptr;

}

bool WarpManager::checkIfExists(int id){
    for(const auto& warp : *warpList)
        if(warp->id == id)
            return true;
    return false;
    
}

bool WarpManager::loadFromFile(string path){
    string loadPath;
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
    
    FILE* f = fopen_s(loadPath.c_str(), "rb");
    if(!f){
        throw runtime_error("[Warp Manager] Could not open: " + loadPath);
        return false;
    }
    int id=-1;
    int size=0;
    bool skipLater=false;
    char _path[255], name[100];
    fread(&size, sizeof(int), 1, f);
    Warp* w=nullptr;
    for(int x=0; x<size;x++){
        fread(&id, sizeof(int), 1, f);
        //IF ALREADY INSERTED SKIP IT
        if(checkIfExists(id)==true){
            Debug::LogManager::log(Debug::LogLevel::WARNING, "[Warp Manager] Skiping object on loadFromFile with id: %T" , id);
            //read all the data, then delete it on the end
            skipLater=true;
        }
        warpList->push_back(new Warp());
        w=warpList->at(warpList->size()-1);
        w->id=id;
        
        fread(&w->size.x, sizeof(int), 1, f);
        fread(&w->size.y, sizeof(int), 1, f);
        
        fread(_path, sizeof(char), 255, f);
        w->path=string(_path);
        
        fread(name, sizeof(char), 100, f);
        w->name=string(name);
        
        fread(&w->destiny.x, sizeof(int), 1, f);
        fread(&w->destiny.y, sizeof(int), 1, f);
        
        if(skipLater){
            warpList->pop_back();
            skipLater=false;
        }
    }
    fclose(f);
    return true;
}
void WarpManager::unloadData(){
    for(int x=0; x<warpList->size(); x++)
        delete warpList->at(x);
    warpList->clear();
}
bool WarpManager::addWarp(Warp* warp){
    if(WarpManager::getWarp(warp->id))return false;
    WarpManager::warpList->push_back(warp);
    return true;
    
}
bool WarpManager::addWarp(int id, string path, string name, Point2i size, Point2i destiny){
    if(WarpManager::getWarp(id))return false;
    else{
        Warp* w=new Warp(id, path, name, size, destiny);
        WarpManager::warpList->push_back(w);
        return true;
    }
}
bool WarpManager::removeWarp(int id){
    for(auto i=warpList->begin(); i!=warpList->end(); i++)
        if((*i)->id == id){
            warpList->erase(i);
            return true;
        }
    return false;
}