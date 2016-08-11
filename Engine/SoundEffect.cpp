//
//  SoundEffect.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "SoundEffect.h"

using namespace Adventure;
SoundEffect::SoundEffect(){}
SoundEffect::SoundEffect(int id, string path, string name, int minPixelDistance) : id(id), path(path), name(name), minPixelDistance(minPixelDistance)
{}
SoundEffect::~SoundEffect(){}

int SoundEffect::getID(){
    return id;
}

string SoundEffect::getPath() const{
    return path;
}
void SoundEffect::setPath(string path){
    this->path=path;
}
string SoundEffect::getName() const{
    return name;
}
void SoundEffect::setName(string name){
    this->name=name;
}
int SoundEffect::getMinPixelDistance(){
    return minPixelDistance;
}
void SoundEffect::setMinPixelDistance(int minPixelDistance){
    this->minPixelDistance=minPixelDistance;
}

float SoundEffect::getAttenuation(){
    return attenuation;
}
void SoundEffect::setAttenuation(float attenuation){
    this->attenuation=attenuation;
}

int SoundEffect::getBothSpeakersArea(){
    return bothSpeakersArea;
}
void SoundEffect::setBothSpeakersArea(int bothSpeakersArea){
    this->bothSpeakersArea=bothSpeakersArea;
}