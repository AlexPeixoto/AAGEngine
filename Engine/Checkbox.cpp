//
//  Checkbox.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Checkbox.h"

using namespace Adventure;

Checkbox::Checkbox(TextControl* textControl,  string text, string backgroundPath, string selectionPath, Point2i textPosition, Color color, function<void (bool, Checkbox*)> callback){
    this->textControl=textControl;
    this->callback=callback;
    this->background=new Image(backgroundPath);
    this->selection=new Image(selectionPath);
    this->textPosition=textPosition;
    this->color=color;
    this->text=text;
}

Checkbox::~Checkbox(){}

void Checkbox::setCheckedCallback(function<void (bool, Checkbox*)> callback){
    this->callback=callback;
}
void Checkbox::changeStatus(bool selected){
    this->selected=selected;
    callback(selected, this);
}
void Checkbox::render(){
    if(background!=nullptr && selection!=nullptr){
        textControl->setColor(color);
        textControl->renderSimpleText(textPosition, text);
        background->render();
        if(selected==true)
            selection->render();
        
    }
}

bool Checkbox::loadBackground(string path){
    try{
        if(background!=nullptr){
            delete background;
            background=nullptr;
        }
        background=new Image("path");
    }
    catch(...){
        return false;
    }
    return true;
}
bool Checkbox::loadSelection(string path){
    try{
        if(selection!=nullptr){
            delete selection;
            selection=nullptr;
        }
        selection=new Image("path");
    }
    catch(...){
        return false;
    }
    return true;
}
void Checkbox::setText(string text){
    this->text=text;
}
void Checkbox::setCheckboxPosition(Point2i position){
    background->setPosition(position);
}
void Checkbox::setCheckboxPosition(int x, int y){
    setCheckboxPosition(Point2i(x, y));
}
void Checkbox::setTextPosition(Point2i position){
    textPosition=position;
}
void Checkbox::setTextColor(Color color){
    this->color=color;
}
void Checkbox::setTextPosition(int x, int y){
    setTextPosition(Point2i(x, y));
}
Point2i Checkbox::getCheckboxPosition(){
    return background->getPosition();
}
Point2i Checkbox::getTextPosition(){
    return textPosition;
}
Vector2i Checkbox::getSize(){
    return background!=nullptr ? (Vector2i)background->getSize() : Vector2i(0, 0);
}
string Checkbox::getText() const{
    return text;
}
Color Checkbox::getTextColor(){
    return color;
}
bool Checkbox::getStatus(){
    return selected;
}