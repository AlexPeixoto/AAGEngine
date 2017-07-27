//
//  Slidebar.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Slidebar.h"

using namespace Adventure;

Slidebar::Slidebar(const std::string& slideBarPath, const std::string& slideElementPath, int minValue, int maxValue, int increaseValue, int valuePerPixel, Point2i position, function<void (int value)> callback){
    
    this->position=position;
    this->valuePerPixel=valuePerPixel;
    this->increaseValue=increaseValue;
    this->callback=callback;
    selectedValue=minValue;
    slideBarImage=new Image(slideBarPath);
    slideElementImage=new Image(slideElementPath);
    slideBarImage->setScale(Vector2f(1, 1));
    slideBarImage->setPosition(position);
    slideElementImage->setPosition(Point2i(position.x, position.y+(slideBarImage->getHeight()/2-slideElementImage->getHeight()/2)));
    if(setValues(minValue, maxValue, increaseValue)==false){
        delete slideBarImage;
        delete slideElementImage;
        throw std::runtime_error("[Slidebar] Invalid values for minValue or/and maxValue or/and increaseValue. minValue and maxValue should be multiple of increasceValue");
    }
}

void Slidebar::render(){
    slideBarImage->render();
    slideElementImage->render();

}

bool Slidebar::prevValue(){
    if(selectedValue-increaseValue>=minValue){
        selectedValue-=increaseValue;
        updateSlidebarPosition();
        callback(selectedValue);
        return true;
    }
    return false;
}
bool Slidebar::nextValue(){
    if(selectedValue+increaseValue<=maxValue){
        selectedValue+=increaseValue;
        updateSlidebarPosition();
        callback(selectedValue);
        return true;
    }
    return false;
    
}
bool Slidebar::setValue(int selectedValue){
    if(selectedValue%increaseValue==0 && selectedValue>=minValue && selectedValue <=maxValue){
        this->selectedValue=selectedValue;
        updateSlidebarPosition();
        callback(selectedValue);
        return true;
    }
    return false;
        
}
int Slidebar::getValue(){
    return selectedValue;
}
void Slidebar::updateSlidebarPosition(){
    //Calculate how many pixels i need
    slideElementImage->setPosition(Point2i(
                                           position.x + valuePerPixel*selectedValue,
                                           position.y+(slideBarImage->getHeight()/2-slideElementImage->getHeight()/2)
                                           ));
}
bool Slidebar::setValues(int minValue, int maxValue, int increaseValue){
    if(minValue%increaseValue==0 && maxValue%increaseValue==0){
        // Set new values
        this->increaseValue=increaseValue;
        this->maxValue=maxValue;
        this->minValue=minValue;
        
        // Lets calculate how much stretch is needed to put the bar to is in the correct size.
        // Value range
        int baseValue=maxValue-minValue;
        // Lets stretch it
            //Calculate how many pixels i need
        int pixelsNeeded=(baseValue*valuePerPixel);
            //Divide pixelsNeeded per number of pixels
        float newStretchValue=(float)pixelsNeeded/((float)slideBarImage->getWidth()-slideElementImage->getWidth()/2);
        slideBarImage->setWidthScale(newStretchValue);
        
        slideElementImage->setPosition(Point2i(
                                               position.x + valuePerPixel*selectedValue,
                                               position.y+(slideBarImage->getHeight()/2-slideElementImage->getHeight()/2)
                                               ));
        return true;
    }
    return false;
}

int Slidebar::getMinValue() const{
    return minValue;
}
int Slidebar::getMaxValue() const{
    return maxValue;
}
int Slidebar::getIncreseValue() const{
    return increaseValue;
}

void Slidebar::setSlideBarImage(const std::string& path){
    delete slideBarImage;
    slideBarImage=new Image(path);
}
void Slidebar::setSlideElementImage(const std::string& path){
    delete slideElementImage;
    slideElementImage=new Image(path);
}

void Slidebar::setSlideBarWidth(int width){
    // Get the actual width and divide by what is wanted so i can stretch it.
    slideBarImage->setWidthScale((slideBarImage->getWidth()/width));
    updateSlidebarPosition();
}
int Slidebar::getSlideBarWidth(){
    return slideBarImage->getWidth();
}
int Slidebar::getStretchedSlideBarWidth(){
    return slideBarImage->getWidth()*slideBarImage->getWidthScale();
}