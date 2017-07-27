//
//  Dropdown.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Dropdown.h"

using namespace Adventure;

Dropdown::Dropdown(TextControl* textControl, int optionsPerScreen, int boxBorder, int optionSpacing, Point2i position, function<void (int, Dropdown*)> callback){
    this->position=position;
    this->textControl=textControl;
    this->callback=callback;
    this->optionsPerScreen=optionsPerScreen;
    this->boxBorder=boxBorder;
    this->optionSpacing=optionSpacing;
    size.x=optionsPerScreen*maxTextHeight+optionSpacing*2;
    size.y=maxTextWidth+optionSpacing+optionSpacing*2;
    maxTextHeight=textControl->getHeight("QWERTYUIOPASDFGHJKLZXCVBNM1234567890");
    menuShape=nullptr;
    optionShape=nullptr;
    boxShape=nullptr;
    selectedOptionIndex=optionIndex=0;
    openMenu=false;
}
Dropdown::~Dropdown(){}

void Dropdown::render(){
    if(menuShape==nullptr || optionShape==nullptr || boxShape==nullptr)
        return;
    // Render the option onthe screen.
    menuShape->render();
    // Spacing just like the options
    if(selectedOptionIndex>=0 && selectedOptionIndex<options.size()){
                                                                  // Text alignment problem (SFML Behavior)
        textControl->renderSimpleText(position.x+optionSpacing, position.y-maxTextHeight/2+optionSpacing, options.size() > 0 ? options.at(selectedOptionIndex) : "");
    }
    // Render here on the menu.
    if(openMenu){
        if(options.size()==0)
            return;
        
                // Same algorithm as the used on the Dialog class.
        // same as optionIndex-(optionIndex%optionsPerScreen)
        int initOption=((optionIndex/optionsPerScreen)*optionsPerScreen);
        // Position and add the size of the shape of the option on the menu. add the box border so i jump the border for the first option.
        int y=position.y+menuShape->getSize().y+optionSpacing*2;
        
        int elementsOnScreen=initOption+optionsPerScreen>options.size()-1 ? initOption%optionsPerScreen : optionsPerScreen;
        boxShape->setSize(Vector2i(maxTextWidth+optionSpacing*2, (maxTextHeight+boxBorder+optionSpacing)*elementsOnScreen));
        boxShape->setPosition(position.x, y);
        boxShape->render();

        
        //optionsPerScreen-1 because it is (zero indexed)
        for(int option=initOption; option<initOption+optionsPerScreen && option < options.size(); option++){
            if(optionIndex==option)
                if(optionShape!=nullptr){
                    optionShape->setSize(maxTextWidth+optionSpacing*2, maxTextHeight+boxBorder+optionSpacing);
                    optionShape->setPosition(position.x, y+optionSpacing);
                    optionShape->render();
                }
            textControl->setColor(menuOptionColor);
            textControl->renderSimpleText(position.x, y, options.at(option));
            y+=optionShape->getSize().y;
        }
    }
}
void Dropdown::intMaxOptionsPerScreen(int optionsPerScreen){
    Vector2i size;
    size.x=position.x;
    this->optionsPerScreen=optionsPerScreen;
}

void Dropdown::setOpenMenu(bool openMenu){
    this->openMenu=openMenu;
}
bool Dropdown::next(){
    if(openMenu && optionIndex<options.size()-1){
        optionIndex++;
        return true;
    }
    return false;
}
bool Dropdown::prev(){
    if(openMenu && optionIndex>0){
        optionIndex--;
        return true;
    }
    return false;
}
void Dropdown::selectOption(){
    if(openMenu){
        selectedOptionIndex=optionIndex;
        openMenu=false;
        callback(selectedOptionIndex, this);
    }
}

void Dropdown::setSelectedCallback(function<void (int, Dropdown*)> callback){
    this->callback=callback;
}
void Dropdown::setMenuOptionColor(Color color){
    menuOptionColor=color;
}
void Dropdown::setSelectedOptionColor(Color color){
    selectedOptionColor=color;
}

Vector2i Dropdown::getSize(){
    return size;
}
void Dropdown::setOptionSpacing(int optionSpacing){
    this->optionSpacing=optionSpacing;
    calculateMenuShapeSize();
}
vector<string> Dropdown::getOptions() const{
    return options;
}
bool Dropdown::getOpenMenu(){
    return openMenu;
}
void Dropdown::setBoxShape(BackgroundShape* boxShape){
    this->boxShape=boxShape;
    this->boxShape->setSize(Vector2i(maxTextHeight*optionsPerScreen+boxBorder, maxTextWidth+boxBorder));
}
void Dropdown::setOptionShape(BackgroundShape* optionShape){
    this->optionShape=optionShape;
    this->optionShape->setSize(Vector2i(maxTextHeight, maxTextWidth));
}
void Dropdown::setMenuShape(BackgroundShape* menuShape){
    this->menuShape=menuShape;
    this->menuShape->setPosition(position);
    // Update boxshape position
    if(boxShape!=nullptr)
        boxShape->setPosition(Point2i(position.x, position.y+menuShape->getSize().y));
}
void Dropdown::calculateMenuShapeSize(){
    int maxWidth=0;
    int maxHeight=0;
    for(auto option : options){
        if(maxWidth<textControl->getWidth(option))
            maxWidth=textControl->getWidth(option);
        if(maxHeight<textControl->getHeight(option))
            maxHeight=textControl->getHeight(option);
    }
    maxTextWidth=maxWidth;
    maxTextHeight=maxHeight;
    size.x=maxTextWidth+optionSpacing*2;
    size.y=maxTextHeight+optionSpacing*2;
    if(menuShape!=nullptr)
        menuShape->setSize(size);

}
void Dropdown::addOption(string option){
    options.push_back(option);
    calculateMenuShapeSize();
}
BackgroundShape* Dropdown::returnBoxShape(){
    return boxShape;
}
BackgroundShape* Dropdown::returnOptionShape(){
    return optionShape;
}
BackgroundShape* Dropdown::returnMenuShape(){
    return menuShape;
}
Color Dropdown::getMenuOptionColor(){
    return menuOptionColor;
}
Color Dropdown::getSelectedOptionColor(){
    return selectedOptionColor;
}
string Dropdown::getOption(int index){
    return options.at(index);
}
int Dropdown::getOptionSpacing(){
    return optionSpacing;
}
bool Dropdown::removeOption(int index){
    if(index < options.size()){
        options.erase(options.begin()+index);
        if(index==selectedOptionIndex){
            if(selectedOptionIndex > 0)
                selectedOptionIndex--;
            else if(selectedOptionIndex==0 && options.size()>0)
                selectedOptionIndex++;
        }
        return true;
    }
    return false;
}