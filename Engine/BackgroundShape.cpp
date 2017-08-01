//
//  Shape.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "BackgroundShape.h"
#include "Location.h"

using namespace Core;

sf::RenderWindow* BackgroundShape::window = nullptr;
string BackgroundShape::relativePath = "";

BackgroundShape::BackgroundShape() : texture(nullptr) {}
BackgroundShape::~BackgroundShape() {
	delete texture;
	texture = nullptr;
}
void BackgroundShape::setWindow(sf::RenderWindow *window) {
	BackgroundShape::window = window;
}
void BackgroundShape::render() {
	shape.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
	shape.setSize(static_cast<Vector2f>(size));
	if (BackgroundShape::window != nullptr) {
		BackgroundShape::window->draw(shape);
	}
}

void BackgroundShape::setBorderSize(int size) {
	shape.setOutlineThickness(static_cast<float>(size));
}
int BackgroundShape::getBorderSize() {
	return static_cast<int>(shape.getOutlineThickness());
}

void BackgroundShape::loadTexture(const std::string& path) {
	delete texture;
	texture = new sf::Texture();
	
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != string::npos)
			//if path have the / on the end
			loadPath = path[path.size() - 1] == '/' ? relativePath + path.substr(lastIndex + 1) : relativePath + "/" + path.substr(lastIndex + 1);
		else
			loadPath = path[path.size() - 1] == '/' ? relativePath + path : relativePath + "/" + path;
	}
	else {
		loadPath = path;
	}
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif

	if (!texture->loadFromFile(loadPath)) {
		delete texture;
		texture = nullptr;
		throw std::runtime_error("[BackgroundShape] Error loading:" + loadPath);
	}
	shape.setTexture(texture);

}
void BackgroundShape::unloadTexture() {
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
		//SFML was not created with C++11 in mind
		shape.setTexture(NULL);
	}
}
void BackgroundShape::setInsideColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	insideColor = Color(r, g, b, a);
	shape.setFillColor(insideColor);
}
void BackgroundShape::setInsideColor(Color c) {
	insideColor = Color(c);
	shape.setFillColor(insideColor);
}
Color BackgroundShape::getInsideColor() {
	return insideColor;
}
void BackgroundShape::setBorderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	outlineColor = Color(r, g, b, a);
	shape.setOutlineColor(outlineColor);
}
void BackgroundShape::setBorderColor(Color c) {
	outlineColor = Color(c);
	shape.setOutlineColor(outlineColor);
}
Color BackgroundShape::getBorderColor() {
	return outlineColor;
}