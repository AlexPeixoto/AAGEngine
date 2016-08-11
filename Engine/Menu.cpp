//
//  Menu.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Menu.h"

using namespace Adventure;

Menu::Menu(string font){
    textControl=new TextControl(font);
}

void Menu::render(){
    for(auto &checkbox : checkboxes)
        if(checkbox!=nullptr)
            checkbox->render();
        
    
    for(auto &information : informations)
        if(information!=nullptr)
            information->render();
    
    for(auto &infImage : informationimage)
        if(infImage!=nullptr)
            infImage->render();
    
    for(auto &slidebar : slidebars)
        if(slidebar!=nullptr)
            slidebar->render();
    
    for(auto &selectable : selectables)
        if(selectable!=nullptr)
            selectable->render();
    
    for(auto &dropdown : dropdowns)
        if(dropdown!=nullptr)
            dropdown->render();
}

void Menu::addCheckbox(Checkbox* checkbox){
    checkboxes.push_back(checkbox);
    elements.push_back(new Element({TYPES::CHECKBOX, (int)checkboxes.size()-1}));
}
void Menu::addCheckbox(string text, string backgroundPath, string selectionPath, Point2i position, Point2i textPosition, Color color, function<void (bool, Checkbox*)> callback){
    checkboxes.push_back(new Checkbox(textControl, text, backgroundPath, selectionPath, textPosition, color, callback));
    checkboxes.at(checkboxes.size()-1)->setPosition(position);
    elements.push_back(new Element({TYPES::CHECKBOX, (int)checkboxes.size()-1}));
}

void Menu::addInformation(Information* information){
    informations.push_back(information);
    elements.push_back(new Element({TYPES::INFORMATION, (int)informations.size()-1}));
    
}
void Menu::addInformation(string information, Vector2f scale, Point2i position, Color color){
    informations.push_back(new Information(textControl, information, scale, position, color));
    elements.push_back(new Element({TYPES::INFORMATION, (int)informations.size()-1}));
}

void Menu::addInformationImage(InformationImage* informationImage){
    informationimage.push_back(informationImage);
    elements.push_back(new Element({TYPES::INFORMATIONIMAGE, (int)informationimage.size()-1}));
}
void Menu::addInformationImage(string imagePath, string text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor){
    informationimage.push_back(new InformationImage(textControl, imagePath, text, imagePosition, textPosition, imageScale, textScale, textColor));
    elements.push_back(new Element({TYPES::INFORMATIONIMAGE, (int)informationimage.size()-1}));
}

void Menu::addSlidebar(Slidebar* slidebar){
    slidebars.push_back(slidebar);
    elements.push_back(new Element({TYPES::SLIDEBAR, (int)slidebars.size()-1}));
}
void Menu::addSlidebar(string slideBarPath, string slideElementPath, int minValue, int maxValue, int increaseValue, int valuePerPixel, Point2i position, function<void (int value)> callback){
    slidebars.push_back(new Slidebar(slideBarPath, slideElementPath, minValue, maxValue, increaseValue, valuePerPixel, position, callback));
    elements.push_back(new Element({TYPES::SLIDEBAR, (int)slidebars.size()-1}));
}
void Menu::addDropdown(Adventure::Dropdown *dropdown){
    dropdowns.push_back(dropdown);
    elements.push_back(new Element({TYPES::DROPDOWN, (int)dropdowns.size()-1}));
}
void Menu::addDropdown(int optionsPerScreen, int boxBorder, int optionSpacing, Point2i position, function<void (int, Dropdown*)> callback){
    dropdowns.push_back(new Dropdown(textControl, optionsPerScreen, boxBorder, optionSpacing, position, callback));
    elements.push_back(new Element({TYPES::DROPDOWN, (int)dropdowns.size()-1}));
}
void Menu::addSelectable(Selectable* selectable){
    selectables.push_back(selectable);
    elements.push_back(new Element({TYPES::SELECTABLE, (int)selectables.size()-1}));
}
void Menu::addSelectable(int numberOfItens, int spacing, Core::BackgroundShape *selectedItem, Vector2i itemSize, Point2i position, function<void (int, Adventure::Selectable *)> callback){
    selectables.push_back(new Selectable(numberOfItens, spacing, selectedItem, itemSize, position, callback));
    elements.push_back(new Element({TYPES::SELECTABLE, (int)selectables.size()-1}));
}
bool Menu::removeElement(int index, bool deletePointer){
    if(index < elements.size()){
        switch( elements.at(index)->type ){
            case TYPES::CHECKBOX :
                if( checkboxes.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete checkboxes.at(elements.at(index)->index);
                    checkboxes.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::DROPDOWN :
                if( dropdowns.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete dropdowns.at(elements.at(index)->index);
                    dropdowns.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::INFORMATIONIMAGE :
                if( informationimage.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete informationimage.at(elements.at(index)->index);
                    informationimage.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::INFORMATION :
                if( informations.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete informations.at(elements.at(index)->index);
                    informations.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::SLIDEBAR :
                if( slidebars.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete slidebars.at(elements.at(index)->index);
                    slidebars.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::SELECTABLE :
                if( selectables.at(elements.at(index)->index) != nullptr ){
                    if(deletePointer)
                        delete selectables.at(elements.at(index)->index);
                    selectables.at(elements.at(index)->index)=nullptr;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

vector<Menu::Element*> Menu::getElements() const{
    return elements;
}

vector<Checkbox*> Menu::getCheckboxes() const{
    return checkboxes;
}

vector<Information*> Menu::getInformations() const{
    return informations;
}

vector<InformationImage*> Menu::getInformationImages() const{
    return informationimage;
}

vector<Slidebar*> Menu::getSlidebars() const{
    return slidebars;
}

vector<Dropdown*> Menu::getDropdowns() const{
    return dropdowns;
}
vector<Selectable*> Menu::getSelectables() const{
    return selectables;
}