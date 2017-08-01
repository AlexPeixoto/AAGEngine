//
//  SoundEffect.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "SoundEffect.h"

using namespace Adventure;

SoundEffect::SoundEffect(int id, const std::string& path, const std::string& name, int minPixelDistance) : id(id), path(path), name(name), minPixelDistance(minPixelDistance)
{}
SoundEffect::~SoundEffect() {}

int SoundEffect::getID() const {
	return id;
}

std::string SoundEffect::getPath() const {
	return path;
}
void SoundEffect::setPath(const std::string& path) {
	this->path = path;
}
std::string SoundEffect::getName() const {
	return name;
}
void SoundEffect::setName(const std::string& name) {
	this->name = name;
}
int SoundEffect::getMinPixelDistance() const {
	return minPixelDistance;
}
void SoundEffect::setMinPixelDistance(int minPixelDistance) {
	this->minPixelDistance = minPixelDistance;
}

float SoundEffect::getAttenuation() const {
	return attenuation;
}
void SoundEffect::setAttenuation(float attenuation) {
	this->attenuation = attenuation;
}

int SoundEffect::getBothSpeakersArea() const {
	return bothSpeakersArea;
}
void SoundEffect::setBothSpeakersArea(int bothSpeakersArea) {
	this->bothSpeakersArea = bothSpeakersArea;
}