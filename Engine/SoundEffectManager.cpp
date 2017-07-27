//
//  SoundEffectManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "SoundEffectManager.h"

using namespace Adventure;

vector<SoundEffect*>* SoundEffectManager::sfxList=sfxList=new vector<SoundEffect*>();;
string SoundEffectManager::relativePath="";
string SoundEffectManager::relativeInstancePath="";

SoundEffectManager::~SoundEffectManager(){
    if(sfxList!=nullptr){
#ifndef _WIN32
        for_each(sfxList->begin(), sfxList->end(), default_delete<SoundEffect>());
#else
		for_each(sfxList->begin(), sfxList->end(),
	[](SoundEffect* se){
	delete se;
});
#endif
        delete sfxList;
        sfxList=nullptr;
    }
}

Sound* SoundEffectManager::createInstance(int id){
    SoundBuffer* sb = new SoundBuffer();
    Sound* s = new Sound();
    for(auto &sfx : *sfxList){
        
        
        string loadPath;
        string path=sfx->getPath();
        if(relativeInstancePath.size()>0){
            size_t lastIndex=path.find_last_of("/");
            if(lastIndex!=string::npos)
                //if path have the / on the end
                loadPath=path[path.size()-1]=='/' ? relativeInstancePath+path.substr(lastIndex+1) : relativeInstancePath+"/"+path.substr(lastIndex+1);
            else
                loadPath=path[path.size()-1]=='/' ? relativeInstancePath+path : relativeInstancePath+"/"+path;
        }
        else
            loadPath=path;
#ifdef _WIN32
		std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
        
        if(sfx->getID()==id){
            if(sb->loadFromFile(loadPath)){
                s->setBuffer(*sb);
                if(sb->getChannelCount()>1){
                    delete sb;
                    throw std::runtime_error("[Sound Effect Manager] More than one channel on the file:" + sfx->getPath());
                }
                return s;
            }
            else
                throw std::runtime_error("[Sound Effect Manager] Could not load:" + sfx->getPath());
        }
    }
    //If i didn't found it
    return nullptr;
}

SoundEffect* SoundEffectManager::getSoundEffect(int id){
    for(auto &sfx : *sfxList)
        if(sfx->getID()==id)
            return sfx;
    return nullptr;
}

bool SoundEffectManager::checkIfExists(int id){
    for(auto &sfx : *sfxList)
        if(sfx->getID()==id)
            return true;
    return false;
}
bool SoundEffectManager::loadFromFile(string path){
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
    
    FILE* f = fopen(loadPath.c_str(), "rb");
    if(!f){
        throw runtime_error("[Sound Effect Manager] Could not open: " + loadPath);
        return false;
    }
    //read the number of sounds
    int sSize=0;
    fread(&sSize, sizeof(int), 1, f);
    //For each item i will read:
    char _path[255];
    char name[100];
    for(int x=0; x<sSize; x++){
        SoundEffect* sfx = new SoundEffect();//MapData::SoundStructure* s = new MapData::SoundStructure;
        //The sound ID
        fread(&(sfx->id), sizeof(int), 1, f);
        //The sound max distance
        fread(&(sfx->minPixelDistance), sizeof(int), 1, f);
        //the sound attenuation
        fread(&(sfx->attenuation), sizeof(float), 1, f);
        //the area from the point on the map that both speakers play the sound
        fread(&(sfx->bothSpeakersArea), sizeof(int), 1, f);
        //The sound file path
        fread(_path, sizeof(char), 255, f);
        sfx->path=_path;
        //The sound name
        fread(name, sizeof(char), 100, f);
        sfx->name=name;
        if(checkIfExists(sfx->id)==true)
            continue;
        sfxList->push_back(sfx);
    }
    fclose(f);
    return true;
}
void SoundEffectManager::unloadData(){
    for(int x=0; x<sfxList->size(); x++)
        delete sfxList->at(x);
    sfxList->clear();
}
bool SoundEffectManager::addSoundEffect(SoundEffect* soundEffect){
    
    if(!checkIfExists(soundEffect->getID())){
        sfxList->push_back(soundEffect);
        return true;
    }
    return false;
}
bool SoundEffectManager::addSoundEffect(int id, string path, string name, int maxPixelDistance){
    if(checkIfExists(id))return false;
    SoundEffect* sfx = new SoundEffect(id, path, name, maxPixelDistance);
    sfxList->push_back(sfx);
    return true;
}
bool SoundEffectManager::removeSoundEffect(int id){
    for(auto i=sfxList->begin(); i!=sfxList->end();i++)
        if((*i)->getID()==id){
            sfxList->erase(i);
            return true;
        }
    return false;
}