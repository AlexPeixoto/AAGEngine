//
//  InformationImage.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/29/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "InformationImage.h"

using namespace Adventure;

InformationImage::InformationImage(TextControl* textControl, string path, string text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor) : textControl(textControl), text(text), imagePosition(imagePosition), textPosition(textPosition), imageScale(imageScale), textScale(textScale), textColor(textColor){
    this->image = new Image(path);
    image->setPosition(imagePosition);
    image->setScale(imageScale);
    
}

void InformationImage::render(){
    textControl->setScale(textScale);
    textControl->setColor(textColor);
    textControl->renderSimpleText(textPosition, text);
    image->render();
}

void InformationImage::setImagePath(string path){
    image->changeImage(path);
}
void InformationImage::setText(string text){
    this->text=text;
}
void InformationImage::setImagePosition(Point2i imagePosition){
    image->setPosition(imagePosition);
    this->imagePosition=imagePosition;
}
void InformationImage::setTextPosition(Point2i textPosition){
    this->textPosition=textPosition;
}
void InformationImage::setImageScale(Vector2f imageScale){
    this->imageScale=imageScale;
    image->setScale(imageScale);
}
void InformationImage::setTextScale(Vector2f textScale){
    this->textScale=textScale;
}
void InformationImage::setTextColor(Color textColor){
    this->textColor=textColor;
}
string InformationImage::getImagePath() const{
    return image->getPath();
}
Image* InformationImage::getImage(){
    return image;
}
string InformationImage::getText(){
    return text;
}
Point2i InformationImage::getImagePosition(){
    return imagePosition;
}
Point2i InformationImage::getTextPosition(){
    return textPosition;
}
Color InformationImage::getTextColor(){
    return textColor;
}
Vector2f InformationImage::getTextScale(){
    return textScale;
}
Vector2f InformationImage::getImageScale(){
    return imageScale;
}