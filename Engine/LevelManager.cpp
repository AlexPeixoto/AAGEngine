//
//  LevelManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "LevelManager.h"
#include <exception>
using namespace Adventure;

int LevelManager::changeTo=-1;

Level* LevelManager::level =nullptr;
bool LevelManager::loading=false;

void LevelManager::loadLevel(Adventure::Level *level){
    if(LevelManager::level!=nullptr)
        throw std::runtime_error("The level is already loaded, please use the changeLevel");
    else
        LevelManager::level=level;
}
void LevelManager::render(){
    if(!LevelManager::loading)
        LevelManager::level->render();
    else
        LevelManager::renderLoading();
}
void LevelManager::renderLoading(){}
void LevelManager::process(){
    if(!LevelManager::loading)
        LevelManager::level->process();
    else
        LevelManager::processLoading();
}
void LevelManager::processLoading(){
}