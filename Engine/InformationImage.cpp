//
//  InformationImage.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/29/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "InformationImage.h"

using namespace Adventure;

InformationImage::InformationImage(TextControl* textControl, cobst string& path, const string& text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor) : textControl(textControl), text(text), imagePosition(imagePosition), textPosition(textPosition), imageScale(imageScale), textScale(textScale), textColor(textColor){
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

void InformationImage::setImagePath(const std::string& path){
    image->changeImage(path);
}
void InformationImage::setText(const std::string& text){
    this->text=text;
}
void InformationImage::setImagePosition(const Point2i& imagePosition){
    image->setPosition(imagePosition);
    this->imagePosition=imagePosition;
}
void InformationImage::setTextPosition(const Point2i& textPosition){
    this->textPosition=textPosition;
}
void InformationImage::setImageScale(const Vector2f& imageScale){
    this->imageScale=imageScale;
    image->setScale(imageScale);
}
void InformationImage::setTextScale(const Vector2f& textScale){
    this->textScale=textScale;
}
void InformationImage::setTextColor(Color textColor){
    this->textColor=textColor;
}
string InformationImage::getImagePath() const{
    return image->getPath();
}
Image* InformationImage::getImage() const{
    return image;
}
string InformationImage::getText() const{
    return text;
}
Point2i InformationImage::getImagePosition() const{
    return imagePosition;
}
Point2i InformationImage::getTextPosition() const{
    return textPosition;
}
Color InformationImage::getTextColor() const{
    return textColor;
}
Vector2f InformationImage::getTextScale() const{
    return textScale;
}
Vector2f InformationImage::getImageScale() const{
    return imageScale;
}