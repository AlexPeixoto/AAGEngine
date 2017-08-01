//
//  Menu.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Menu.h"

using namespace Adventure;

Menu::Menu(const std::string& font){
    textControl=new TextControl(font);
}

void Menu::render(){
	for (auto &checkbox : checkboxes) {
		if (checkbox != nullptr) {
			checkbox->render();
		}
	}
    
	for (auto &information : informations) {
		if (information != nullptr) {
			information->render();
		}
	}
    
	for (auto &infImage : informationimage) {
		if (infImage != nullptr) {
			infImage->render();
		}
	}
    
	for (auto &slidebar : slidebars) {
		if (slidebar != nullptr) {
			slidebar->render();
		}
	}
    
	for (auto &selectable : selectables) {
		if (selectable != nullptr) {
			selectable->render();
		}
	}
    
	for (auto &dropdown : dropdowns) {
		if (dropdown != nullptr) {
			dropdown->render();
		}
	}
}

void Menu::addCheckbox(Checkbox* checkbox){
    checkboxes.emplace_back(checkbox);
    elements.emplace_back(new Element({TYPES::CHECKBOX, (int)checkboxes.size()-1}));
}
void Menu::addCheckbox(const std::string& text, const std::string& backgroundPath, const std::string& selectionPath, Point2i position, Point2i textPosition, Color color, std::function<void (bool, Checkbox*)> callback){
    checkboxes.emplace_back(new Checkbox(textControl, text, backgroundPath, selectionPath, textPosition, color, callback));
    checkboxes.at(checkboxes.size()-1)->setPosition(position);
    elements.emplace_back(new Element({TYPES::CHECKBOX, (int)checkboxes.size()-1}));
}

void Menu::addInformation(Information* information){
    informations.emplace_back(information);
    elements.emplace_back(new Element({TYPES::INFORMATION, (int)informations.size()-1}));
    
}
void Menu::addInformation(const std::string& information, Vector2f scale, Point2i position, Color color){
    informations.emplace_back(new Information(textControl, information, scale, position, color));
    elements.emplace_back(new Element({TYPES::INFORMATION, (int)informations.size()-1}));
}

void Menu::addInformationImage(InformationImage* informationImage){
    informationimage.emplace_back(informationImage);
    elements.emplace_back(new Element({TYPES::INFORMATIONIMAGE, (int)informationimage.size()-1}));
}
void Menu::addInformationImage(const std::string& imagePath, const std::string& text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor){
    informationimage.emplace_back(new InformationImage(textControl, imagePath, text, imagePosition, textPosition, imageScale, textScale, textColor));
    elements.emplace_back(new Element({TYPES::INFORMATIONIMAGE, (int)informationimage.size()-1}));
}

void Menu::addSlidebar(Slidebar* slidebar){
    slidebars.emplace_back(slidebar);
    elements.emplace_back(new Element({TYPES::SLIDEBAR, (int)slidebars.size()-1}));
}
void Menu::addSlidebar(const std::string& slideBarPath, const std::string& slideElementPath, int minValue, int maxValue, int increaseValue, int valuePerPixel, Point2i position, std::function<void (int value)> callback){
    slidebars.emplace_back(new Slidebar(slideBarPath, slideElementPath, minValue, maxValue, increaseValue, valuePerPixel, position, callback));
    elements.emplace_back(new Element({TYPES::SLIDEBAR, (int)slidebars.size()-1}));
}
void Menu::addDropdown(Adventure::Dropdown *dropdown){
    dropdowns.emplace_back(dropdown);
    elements.emplace_back(new Element({TYPES::DROPDOWN, (int)dropdowns.size()-1}));
}
void Menu::addDropdown(int optionsPerScreen, int boxBorder, int optionSpacing, Point2i position, std::function<void (int, Dropdown*)> callback){
    dropdowns.emplace_back(new Dropdown(textControl, optionsPerScreen, boxBorder, optionSpacing, position, callback));
    elements.emplace_back(new Element({TYPES::DROPDOWN, (int)dropdowns.size()-1}));
}
void Menu::addSelectable(Selectable* selectable){
    selectables.emplace_back(selectable);
    elements.emplace_back(new Element({TYPES::SELECTABLE, (int)selectables.size()-1}));
}
void Menu::addSelectable(int numberOfItens, int spacing, Core::BackgroundShape *selectedItem, Vector2i itemSize, Point2i position, std::function<void (int, Adventure::Selectable *)> callback){
    selectables.emplace_back(new Selectable(numberOfItens, spacing, selectedItem, itemSize, position, callback));
    elements.emplace_back(new Element({TYPES::SELECTABLE, (int)selectables.size()-1}));
}
bool Menu::removeElement(int index, bool deletePointer){
    if(index < elements.size()){
        switch( elements.at(index)->type ){
            case TYPES::CHECKBOX :
                if( checkboxes.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete checkboxes.at(elements.at(index)->index);
					}
                    checkboxes.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::DROPDOWN :
                if( dropdowns.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete dropdowns.at(elements.at(index)->index);
					}
                    dropdowns.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::INFORMATIONIMAGE :
                if( informationimage.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete informationimage.at(elements.at(index)->index);
					}
                    informationimage.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::INFORMATION :
                if( informations.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete informations.at(elements.at(index)->index);
					}
                    informations.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::SLIDEBAR :
                if( slidebars.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete slidebars.at(elements.at(index)->index);
					}
                    slidebars.at(elements.at(index)->index)=nullptr;
                }
                break;
            case TYPES::SELECTABLE :
                if( selectables.at(elements.at(index)->index) != nullptr ){
					if (deletePointer) {
						delete selectables.at(elements.at(index)->index);
					}
                    selectables.at(elements.at(index)->index)=nullptr;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

const std::vector<Menu::Element*>& Menu::getElements() const{
    return elements;
}

const std::vector<Checkbox*>& Menu::getCheckboxes() const{
    return checkboxes;
}

const std::vector<Information*>& Menu::getInformations() const{
    return informations;
}

const std::vector<InformationImage*>& Menu::getInformationImages() const{
    return informationimage;
}

const std::vector<Slidebar*>& Menu::getSlidebars() const{
    return slidebars;
}

const std::vector<Dropdown*>& Menu::getDropdowns() const{
    return dropdowns;
}
const std::vector<Selectable*>& Menu::getSelectables() const{
    return selectables;
}