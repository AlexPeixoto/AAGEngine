//
//  Checkbox.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Checkbox.h"

using namespace Adventure;

Checkbox::Checkbox(TextControl* textControl, const std::string& text, const std::string& backgroundPath, const std::string& selectionPath, Point2i textPosition, Color color, std::function<void (bool, Checkbox*)> callback){
    this->textControl=textControl;
    this->callback=callback;
    this->background=new Image(backgroundPath);
    this->selection=new Image(selectionPath);
    this->textPosition=textPosition;
    this->color=color;
    this->text=text;
}

Checkbox::~Checkbox(){}

void Checkbox::setCheckedCallback(std::function<void (bool, Checkbox*)> callback){
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

bool Checkbox::loadBackground(const std::string& path){
    try{
        delete background;
        background=nullptr;
        background=new Image("path");
    }
    catch(...){
        return false;
    }
    return true;
}
bool Checkbox::loadSelection(const std::string& path){
    try{
        delete selection;
        selection=nullptr;
        selection=new Image("path");
    }
    catch(...){
        return false;
    }
    return true;
}
void Checkbox::setText(const std::string& text){
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
Point2i Checkbox::getCheckboxPosition() const{
    return background->getPosition();
}
Point2i Checkbox::getTextPosition() const{
    return textPosition;
}
Vector2i Checkbox::getSize() const{
    return background!=nullptr ? (Vector2i)background->getSize() : Vector2i(0, 0);
}
std::string Checkbox::getText() const{
    return text;
}
Color Checkbox::getTextColor() const{
    return color;
}
bool Checkbox::getStatus() const{
    return selected;
}