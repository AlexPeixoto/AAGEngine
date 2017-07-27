//
//  ScreenLog.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ScreenLog.h"

using namespace Debug;

//Needs to initialize the font
ScreenLog::ScreenLog(string font):TextControl(font){
    index=-1;
}
ScreenLog::~ScreenLog(){}

bool ScreenLog::gotoScreen(int index){
    if(index < 0 || index >= TextControl::numberOfScreens())
        return false;
    this->index=index;
    return true;
}
bool ScreenLog::next(){
    if(index+1 >= TextControl::numberOfScreens())
        return false;
    index++;
    return true;
    
}
bool ScreenLog::prev(){
    if(index-1 < 0)
        return false;
    index--;
    return true;
}
void ScreenLog::last(){
    index=-1;
}
void ScreenLog::splitInScreens(){
	TextControl::splitInScreens(this->size.x, this->size.y);
}
void ScreenLog::render(){
    if(position.x<0 || position.y<0 || size.x<0 || size.y<0)
        throw domain_error("[ScreenLog] Invalid point on the screen or invalid size");
    int tmpIndex=index;
    if(tmpIndex==-1){
        tmpIndex=TextControl::numberOfScreens()-1;
    }
    if(tmpIndex<0 || tmpIndex >= TextControl::numberOfScreens()){
        //If out of bounds render nothing
        return;
    }
    else{
        TextControl::renderScreen(position, tmpIndex);
    }
        
}
void ScreenLog::flush(){}