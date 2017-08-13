//
//  Image.cpp
//  OpenGL Window
//
//  Created by Alex Peixoto on 11/22/13.
//  Copyright (c) 2013 Alex Peixoto. All rights reserved.
//

#include "Image.h"
#include "Game.h"
using namespace Core;

RenderWindow * Image::window = nullptr;
std::string Image::relativePath = "";

Image::Image(const std::string& path) {
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != std::string::npos)
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
	this->path = loadPath;
	texture = new sf::Texture();
	if (!texture->loadFromFile(loadPath)) {
		throw std::runtime_error("[Image] Impossible to load file: " + loadPath);
	}
	sprite = new sf::Sprite(*texture);
	frameSize = Vector2f(1.0f, 1.0f);
	textureSize = texture->getSize();
	rotation = 0;
	reloading = false;
}
Image::~Image() {
	delete texture;
	delete sprite;
}
void Image::setWindow(sf::RenderWindow *window) {
	Image::window = window;
}
void Image::changeImage(const std::string& path) {
	reloading = true;

	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;

	Image::Image(path.c_str());
}
int Image::getHeight() const {
	return textureSize.y;
}
int Image::getWidth() const {
	return textureSize.x;
}
float Image::getRotation() const {
	return rotation;
}
Vector2<unsigned> Image::getSize() const {
	return textureSize;
}
void Image::setScale(Vector2f scale) {
	frameSize = scale;
}
void Image::setHeightScale(float height) {
	//The height in px
	frameSize.y = height;
}
void Image::setWidthScale(float width) {
	//The height in px
	frameSize.x = width;
}
float Image::getWidthScale() const {
	return frameSize.x;
}
float Image::getHeightScale() const {
	return frameSize.y;
}
Vector2f Image::getScale() const {
	return frameSize;
}
void Image::setX(int x) {
	framePos.x = x;
}
void Image::setY(int y) {
	framePos.y = y;
}
int Image::getX() const {
	return framePos.x;
}
int Image::getY() const {
	return framePos.y;
}
Point2i Image::getPosition() const {
	return framePos;
}
void Image::setPosition(int x, int y) {
	framePos.x = x;
	framePos.y = y;
}
void Image::setPosition(Point2i position) {
	framePos = position;
}
void Image::setRotation(float rotation) {
	this->rotation = rotation;
	sprite->setRotation(rotation);
}
void Image::setOrigin(Point2i origin) {
	this->origin = origin;
	sprite->setOrigin(static_cast<float>(origin.x), static_cast<float>(origin.y));
}
Point2i Image::getOrigin() const {
	return origin;
}
std::string Image::getPath() const {
	return path;
}
void Image::render() {
	if (reloading || Image::window == nullptr) {
		return;
	}
	sprite->setPosition(static_cast<float>(framePos.x), static_cast<float>(framePos.y));
	sprite->setScale(frameSize.x, frameSize.y);
	window->draw(*sprite);
}
void Image::renderSub(Point2f position, Vector2f size) {
	renderSub(position.x, position.y, size.x, size.y);
}
void Image::renderSub(float x, float y, float width, float height) {
	if (reloading || Image::window == nullptr) {
		return;
	}
	this->sprite->setScale(this->frameSize.x, this->frameSize.y);
	this->sprite->setTextureRect(sf::IntRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)));
	this->sprite->setPosition(static_cast<float>(this->framePos.x), static_cast<float>(this->framePos.y));
	Image::window->draw(*this->sprite);
}
sf::Sprite* Image::getSfSprite() {
	return sprite;
}
sf::Texture* Image::getSfTexture() {
	return texture;
}