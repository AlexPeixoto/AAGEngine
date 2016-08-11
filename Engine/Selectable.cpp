//
//  Selectable.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Selectable.h"

using namespace Adventure;

Selectable::Selectable(int numberOfItensPerScreen, int spacing, BackgroundShape* selectedItem, Vector2i itemSize, Point2i position, function<void (int, Selectable*)> callback) : numberOfItensPerScreen(numberOfItensPerScreen), spacing(spacing), selectedItem(selectedItem), itemSize(itemSize), callback(callback){
    selectedItemIndex=0;
    this->position=position;
    this->selectedItem->setSize(itemSize.x+spacing*2, itemSize.y+spacing*2);
    
}

void Selectable::render(){
    if(itens.size()==0)
        return;
    if(selectedItem!=nullptr)
        selectedItem->render();
    
    int initItem=((selectedItemIndex/numberOfItensPerScreen)*numberOfItensPerScreen);
    int x=position.x+spacing*2;
    
    for(int item=initItem; item<initItem+numberOfItensPerScreen && item < itens.size(); item++){
        if(selectedItemIndex==item)
            if(selectedItem!=nullptr){
                //I already added the spacing to the i
                selectedItem->setPosition(x, position.y);
                selectedItem->render();
            }
        itens.at(item)->setPosition(Point2i(x+spacing, position.y+spacing));
        itens.at(item)->render();
        x+=selectedItem->getSize().x+itemSize.x;
    }
    
}
void Selectable::selectOption(){
    callback(selectedItemIndex, this);
}
void Selectable::selectByMouse(Point2i clickedPosition){
    int initItem=((selectedItemIndex/numberOfItensPerScreen)*numberOfItensPerScreen);
    int x=position.x+spacing*2;
    
    for(int item=initItem; item<initItem+numberOfItensPerScreen && item < itens.size(); item++){
        if(clickedPosition.x >= x && clickedPosition.x <= x+itemSize.x &&
           clickedPosition.y >= position.y && clickedPosition.y <= position.y+itemSize.y)
            selectedItemIndex=item;
        x+=selectedItem->getSize().x+itemSize.x;
    }
}
void Selectable::nextItem(){
    if(selectedItemIndex<itens.size()-1)
        selectedItemIndex++;
}
void Selectable::prevItem(){
    if(selectedItemIndex>0)
        selectedItemIndex--;
}

void Selectable::setNumberOfItensPerScreen(int numberOfItensPerScreen){
    this->numberOfItensPerScreen=numberOfItensPerScreen;
}
void Selectable::setSpacing(int spacing){
    this->spacing=spacing;
    this->selectedItem->setSize(itemSize.x+spacing*2, itemSize.y+spacing*2);
}
void Selectable::setSelectedShape(BackgroundShape* selectedItem){
    this->selectedItem=selectedItem;
    this->selectedItem->setSize(itemSize.x+spacing, itemSize.y+spacing);
}
void Selectable::addItem(string path){
    itens.push_back(new Core::Image(path));
}

int Selectable::getNumberOfItensPerScreen(){
    return numberOfItensPerScreen;
}
int Selectable::getSpacing(){
    return spacing;
}
BackgroundShape* Selectable::getSelectedItemBackground(){
    return selectedItem;
}
Image* Selectable::getItem(int index){
    if(index < itens.size())
        return itens.at(index);
    return nullptr;
}
vector<Image*> Selectable::getItens() const{
    return itens;
}

bool Selectable::removeItem(int index){
    if(index < itens.size()){
        itens.erase(itens.begin()+index);
        if(index==selectedItemIndex){
            if(selectedItemIndex > 0)
                selectedItemIndex--;
            else if(selectedItemIndex==0 && itens.size()>0)
                selectedItemIndex++;
        }
        return true;
    }
    return false;
}