//
//  SoundMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "SoundMap.h"

using namespace Adventure;

std::string SoundMap::relativePath="";

SoundMap::SoundMap(){
    sounds=new std::vector<SoundMapStructure*>();
    position=Point2i(-1,-1);
}
SoundMap::SoundMap(const std::string& path) : SoundMap(){
    std::string loadPath;
    if(relativePath.size()>0){
        size_t lastIndex=path.find_last_of("/");
        if(lastIndex!=std::string::npos)
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
    if(!fopen_s(&f, loadPath.c_str(), "rb"))
        throw std::runtime_error("[Item Map] Impossible to load file: " + loadPath);
    int soundsMapSize=-1;
    fread(&soundsMapSize, sizeof(int), 1, f);
    for(int x=0; x<soundsMapSize; x++){
        SoundMapStructure* sms = new SoundMapStructure();
        fread(sms, sizeof(SoundMapStructure), 1, f);
        sms->sound=SoundEffectManager::createInstance(sms->id);
        if(sms->sound==nullptr)
            continue;
        sms->sound->setMinDistance((float)SoundEffectManager::getSoundEffect(sms->id)->getMinPixelDistance());
        sms->sound->setAttenuation(SoundEffectManager::getSoundEffect(sms->id)->getAttenuation());
        sms->sound->setLoop(true);
        sounds->push_back(sms);
        
    }
    fclose(f);
}
SoundMap::~SoundMap(){
    if(sounds!=nullptr){
#ifndef _WIN32
        for_each(sounds->begin(), sounds->end(), default_delete<SoundMapStructure>());
#else
		for_each(sounds->begin(), sounds->end(),
			[](SoundMapStructure* sms){
			delete sms;
		});
#endif
        delete sounds;
        sounds=nullptr;
    }
}
void SoundMap::playAll(){
    if(position==sf::Point2i(-1, -1))
        throw std::runtime_error("[Sound Map] First define the position with updatePosition");
    for(auto &s : *sounds)
        s->sound->play();
}
bool SoundMap::addSound(SoundMapStructure* sms){
    for(auto &s : *sounds)
        if(s->position==sms->position)
            return false;
    sounds->push_back(sms);
    return true;
}
void SoundMap::removeSound(Point2i position){
    for(auto i=sounds->begin(); i!=sounds->end(); i++)
        if((*i)->position==position){
            sounds->erase(i);
            break;
        }
}
void SoundMap::removeSound(int id){
    for(auto i=sounds->rbegin(); i!=sounds->rend(); i++)
        if((*i)->id==id)
            //Reverse iterator erase
            sounds->erase( next(i).base() );
}

void SoundMap::updatePosition(Point2i position){
    this->position=position;
    int bothSpeakersArea=0;
    Point2i differentPosition;
    for(auto &s : *sounds){
        differentPosition=s->position-position;
        bothSpeakersArea=SoundEffectManager::getSoundEffect(s->id)->getBothSpeakersArea();
        //cout << differentPosition.x << "-" << differentPosition.y << endl;
        //On both
        if(abs(differentPosition.x) <= bothSpeakersArea && abs(differentPosition.y) <= bothSpeakersArea)
            s->sound->setPosition(0, 0, 0);
        else
			s->sound->setPosition((float)differentPosition.x, (float)differentPosition.y, 0);
    }    
}
SoundMap::SoundMapStructure* SoundMap::getSound(Point2i position){
    for(auto i=sounds->begin(); i!=sounds->end(); i++)
        if((*i)->position==position)
            return *i;
    return nullptr;
}
std::vector<SoundMap::SoundMapStructure*>* SoundMap::getSounds() const{
    return sounds;
}
