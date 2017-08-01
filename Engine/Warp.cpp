//
//  Warp.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Warp.h"

using namespace Adventure;

Warp::Warp(int id, const std::string& path, const std::string& name, int width, int height, int destinyX, int destinyY)
	: id(id), path(path), name(name), size(Vector2i(width, height)), destiny(Point2i(destinyX, destinyY))
{}

Warp::Warp(int id, const std::string& path, const std::string& name, Vector2i size, Point2i destiny) : id(id), path(path), name(name), size(size), destiny(destiny) {}

Warp::~Warp() {}

void Warp::setPath(const std::string& path) {
	this->path = path;
}
void Warp::setSize(int width, int height) {
	size = Vector2i(width, height);
}
void Warp::setSize(Vector2i size) {
	this->size = size;
}
void Warp::setDestiny(int x, int y) {
	destiny = Point2i(x, y);
}
void Warp::setDestiny(Point2i destiny) {
	this->destiny = destiny;
}
void Warp::setName(const std::string& name) {
	this->name = name;
}

std::string Warp::getPath() const {
	return path;
}
std::string Warp::getName() const {
	return name;
}
Vector2i Warp::getSize() const {
	return size;
}
Point2i Warp::getDestiny() const {
	return destiny;
}
int Warp::getId() const {
	return id;
}