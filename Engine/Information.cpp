//
//  Information.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/29/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Information.h"

using namespace Adventure;

Information::Information(TextControl* textControl, string text, Vector2f scale, Point2i position, Color color) : textControl(textControl), text(text), scale(scale), position(position), color(color){}
void Information::render(){
    textControl->setColor(color);
    textControl->setScale(scale);
    textControl->renderSimpleText(position, text);
}

void Information::setColor(Color color){
    this->color=color;
}
void Information::setScale(Vector2f scale){
    this->scale=scale;
}
void Information::setText(string text){
    this->text=text;
}
void Information::setPosition(Point2i position){
    this->position=position;
}

Color Information::getColor(){
    return color;
}
Vector2f Information::getScale(){
    return scale;
}
string Information::getText(){
    return text;
}
Point2i Information::getPosition(){
    return position;
}