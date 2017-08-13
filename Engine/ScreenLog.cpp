//
//  ScreenLog.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ScreenLog.h"

using namespace Debug;

//Needs to initialize the font
ScreenLog::ScreenLog(const std::string& font) :TextControl(font) {
	index = -1;
}
ScreenLog::~ScreenLog() {}

bool ScreenLog::gotoScreen(int index) {
	if (index < 0 || index >= TextControl::getNumberOfScreens())
		return false;
	this->index = index;
	return true;
}
bool ScreenLog::next() {
	if (index + 1 >= TextControl::getNumberOfScreens())
		return false;
	index++;
	return true;

}
bool ScreenLog::prev() {
	if (index - 1 < 0)
		return false;
	index--;
	return true;
}
void ScreenLog::last() {
	index = -1;
}
void ScreenLog::splitInScreens() {
	TextControl::splitInScreens(this->size.x, this->size.y);
}
void ScreenLog::render() {
	if (position.x < 0 || position.y < 0 || size.x < 0 || size.y < 0)
		throw std::domain_error("[ScreenLog] Invalid point on the screen or invalid size");
	int tmpIndex = index;
	if (tmpIndex == -1) {
		tmpIndex = static_cast<int>(TextControl::getNumberOfScreens() - 1);
	}
	if (tmpIndex < 0 || tmpIndex >= TextControl::getNumberOfScreens()) {
		//If out of bounds render nothing
		return;
	}
	else {
		TextControl::renderScreen(position, tmpIndex);
	}
}
void ScreenLog::flush() {}