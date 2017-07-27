//
//  ItemManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/11/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ItemManager.h"

using namespace Adventure;

vector<Item*> *ItemManager::itemList=new vector<Item*>();
string ItemManager::relativePath="";

ItemManager::~ItemManager(){
    if(itemList!=nullptr){
#ifndef _WIN32
        for_each(itemList->begin(), itemList->end(), default_delete<Item>());
#else
for_each(itemList->begin(), itemList->end(),
	[](Item* i){
	delete i;
});
#endif
        delete itemList;
        itemList=nullptr;
    }
}

void ItemManager::render(int id, Point2i position){
    for(const auto& item : *itemList)
        if(item->id == id){
            if(item->itemSprite==nullptr){
                item->loadSprite();
                item->setPosition(position);
            }
            item->render();
        }
    
}

Item* ItemManager::getItem(int id) {
    for(const auto& item : *itemList)
        if(item->id == id)
            return item;
    return nullptr;
}
bool ItemManager::loadSprite(int id){
    for(const auto& item : *itemList)
        if(item->id == id){
            item->loadSprite();
            return true;
        }
    return false;
    
}

bool ItemManager::checkIfExists(int id){
    for(const auto& item : *itemList)
        if(item->id == id)
            return true;
    return false;
}

//Need to check first if that item exists
bool ItemManager::loadFromFile(string path){
    string loadPath;
    if(relativePath.size()>0){
        size_t lastIndex=path.find_last_of("/");
        if(lastIndex!=string::npos)
            //if path have the / on the end
            loadPath=path[path.size()-1]=='/' ? relativePath+path.substr(lastIndex+1) : relativePath+"/"+path.substr(lastIndex+1);
        else
            loadPath=path[path.size()-1]=='/' ? relativePath+path : relativePath+"/"+path;
    }
    else
        loadPath=path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
    
	FILE* f;

    if(!fopen_s(&f, loadPath.c_str(), "rb")){
        throw std::runtime_error("[Item Manager] Could not open: " + loadPath);
        return false;
    }
    Item* i=nullptr;;
    int size=0;
    int id=-1;
    char _path[255], name[100];
    //Read how many itens i have stored in the file
    fread(&size, sizeof(int), 1, f);
    for(int x=0; x<size;x++){
        fread(&id, sizeof(int), 1, f);
        
        //IF ALREADY INSERTED SKIP IT
        if(checkIfExists(id)==true){
            Debug::LogManager::log(Debug::LogLevel::WARNING, "[Item Manager] Skiping item on loadFromFile with id: %T" , id);
            continue;
        }
        ItemManager::itemList->push_back(new Item());
        i=ItemManager::itemList->at(ItemManager::itemList->size()-1);
        if(i==nullptr||i==NULL)
			break;
        i->id=id;
        fread(&i->tileSize.x, sizeof(int), 1, f);
        fread(&i->tileSize.y, sizeof(int), 1, f);

        fread(_path, sizeof(char), 255, f);
        i->path=string(_path);

        fread(name, sizeof(char), 100, f);
        i->name=string(name);
        
        int pSize;
        fread(&pSize, sizeof(int), 1, f);
        for(int y=0; y<pSize; y++){
            //I will write the key string size + 1  \0 terminator
            int kSize;
            fread(&kSize, sizeof(int), 1, f);

            char* kChar=new char[kSize];
            //Now i will write THE key
            fread(kChar, sizeof(char), kSize, f);
            
            
            int vSize;
            //I will write the value string size + 1  \0 terminator
            fread(&vSize, sizeof(int), 1, f);

            char* kValue=new char[vSize];
            
            //Now i will write THE value
            fread(kValue, sizeof(char), vSize, f);
            
            if(i->properties->find(string(kChar))!=i->properties->end()){
                Debug::LogManager::log(Debug::LogLevel::WARNING, "[Item Manager] Skiping item property on loadFromFile with itemId: %T and propertyKey: %T" , id, kChar);
                continue;
            }
            
            i->properties->insert(make_pair(string(kChar), string(kValue)));
            free(kChar);
            free(kValue);
        }
    }
    return true;
}
void ItemManager::unloadData(){
    for(int x=0; x<itemList->size(); x++)
        delete itemList->at(x);
    itemList->clear();
}
bool ItemManager::addItem(Item* item){
    if(ItemManager::getItem(item->id))return false;
    ItemManager::itemList->push_back(item);
    return true;
}
bool ItemManager::addItem(int id, const std::string& path, const std::string& name, Vector2i tileSize){
    if(ItemManager::getItem(id))return false;
    else{
        Item* i=new Item(id, path, name, tileSize);
        ItemManager::itemList->push_back(i);
        return true;
    }
}
bool ItemManager::removeItem(int id){
    for(auto i=ItemManager::itemList->begin(); i!=ItemManager::itemList->end(); i++)
        if((*i)->id == id){
            ItemManager::itemList->erase(i);
            return true;
        }
    return false;
}