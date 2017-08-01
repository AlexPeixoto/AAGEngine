//
//  ObjectMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ObjectMap.h"

using namespace Adventure;
using Core::Collision;

std::string ObjectMap::relativePath = "";

ObjectMap::ObjectMap() {
	objectList = new std::vector<ObjectFake*>();
}
ObjectMap::ObjectMap(const std::string& path) {
	objectList = new std::vector<ObjectFake*>();
	int size;
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != std::string::npos) {
			//if path have the / on the end
			loadPath = path[path.size() - 1] == '/' ? relativePath + path.substr(lastIndex + 1) : relativePath + "/" + path.substr(lastIndex + 1);
		}
		else {
			loadPath = path[path.size() - 1] == '/' ? relativePath + path : relativePath + "/" + path;
		}
	}
	else
		loadPath = path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif

	FILE* f;
	if (!fopen_s(&f, loadPath.c_str(), "rb"))
		throw std::runtime_error("[Object Map] Impossible to load file: " + loadPath);

	fread(&size, sizeof(int), 1, f);

	for (int x = 0; x < size; ++x) {
		ObjectFake *o = new ObjectFake;
		fread(&o->id, sizeof(int), 1, f);
		fread(&o->position, sizeof(Point2i), 1, f);
		o->spriteIndex = sf::Point2i(1, 1);
		o->collidable = true;
		objectList->push_back(o);
	}
	fclose(f);
}
ObjectMap::~ObjectMap() {
	if (objectList != nullptr) {
#ifndef _WIN32
		for_each(objectList->begin(), objectList->end(), default_delete<ObjectFake>());
#else
		for_each(objectList->begin(), objectList->end(),
			[](ObjectFake* of) {
			delete of;
		});
#endif
		delete objectList;
		objectList = nullptr;
	}
}
bool ObjectMap::collided(Core::Collision::BoundingBox b, Vector2f movement) {
	return collidedWith(b, movement) >= 0;
}
int ObjectMap::collidedWith(Core::Collision::BoundingBox b, Vector2f movement) {
	for (size_t x = 0; x < objectList->size(); ++x) {
		ObjectFake* object = objectList->at(x);
		if (!object->collidable)
			continue;
		Object* o = ObjectManager::getObject(object->id);
		if (o != nullptr) {
			//Here i check if my item collides with the area, if so it means it is on the visible area
			//Item Bounding box
			Core::Collision::BoundingBox objectBB;
			objectBB.size = (Vector2f)o->getTileSize();
			objectBB.position = (Point2f)object->position + (Vector2f)movement;
			if (Core::Collision::collidedAABB(objectBB, b)) {
				return x;
			}
		}
	}
	return -1;
}
void ObjectMap::setSpriteIndex(size_t index, Point2i spriteIndex) {
	if (index >= objectList->size()) {
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	}
	objectList->at(index)->spriteIndex = spriteIndex;
}
void ObjectMap::setSpriteIndex(size_t index, int spriteIndexX, int spriteIndexY) {
	setSpriteIndex(index, Point2i(spriteIndexX, spriteIndexY));
}
void ObjectMap::setCollidable(size_t index, bool collidable) {
	if (index >= objectList->size()) {
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	}
	objectList->at(index)->collidable = collidable;

}
Point2i ObjectMap::getSpriteIndex(size_t index) const {
	if (index >= objectList->size())
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	return objectList->at(index)->spriteIndex;
}
int ObjectMap::getSpriteIndexX(size_t index) const {
	if (index >= objectList->size()) {
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	}
	return objectList->at(index)->spriteIndex.x;
}

int ObjectMap::getSpriteIndexY(size_t index) const {
	if (index >= objectList->size())
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	return objectList->at(index)->spriteIndex.y;
}

bool ObjectMap::getIsCollidable(size_t index) const {
	if (index >= objectList->size()) {
		throw std::runtime_error("[Object Map] There is not an object at the specified index");
	}
	return objectList->at(index)->collidable;
}
void ObjectMap::addObject(int id, int x, int y, int spriteIndexX, int spriteIndexY) {
	addObject(id, Point2i(x, y), Point2i(spriteIndexX, spriteIndexY));
}
void ObjectMap::addObject(int id, Point2i position, Point2i spriteIndex) {
	ObjectFake* o = new ObjectFake();
	o->id = id;
	o->position = position;
	o->spriteIndex = spriteIndex;
	objectList->push_back(o);
}
void ObjectMap::removeObject(size_t index) {
	if (index < objectList->size()) {
		objectList->at(index) = nullptr;
	}
}
void ObjectMap::render(int x, int y, int width, int height) {
	render(Point2i(x, y), Vector2i(width, height));
}
void ObjectMap::render(Point2i position, Vector2i size) {
	Point2i renderPosition;
	for (auto const& object : *objectList) {

		Object* o = ObjectManager::getObject(object->id);
		if (o != nullptr) {
			//Here i check if my object collides with the area, if so it means it is on the visible area
			//Object Bounding box
			Core::Collision::BoundingBox objectBB;
			o->setPosition(object->position);
			objectBB.size = (Vector2f)o->getTileSize();
			objectBB.position = (Point2f)o->getPosition();
			if (objectBB.position.x + objectBB.size.x > 0 && objectBB.position.y + objectBB.size.y > 0) {
				o->setTileIndex(object->spriteIndex);
				o->setPosition(Point2i(objectBB.position));
				o->setTileSize(o->getTileSize());
				o->render();
			}
		}
	}
}
void ObjectMap::renderPerfect(int x, int y, int width, int height, int moveX, int moveY) {
	renderPerfect(Point2i(x, y), Vector2i(width, height), Vector2i(moveX, moveY));
}
void ObjectMap::renderPerfect(Point2i position, Vector2i size, Vector2i movement) {
	Point2i renderPosition;
	for (auto const& object : *objectList) {

		Object* o = ObjectManager::getObject(object->id);
		if (o != nullptr) {
			//Here i check if my object collides with the area, if so it means it is on the visible area
			//Object Bounding box
			Core::Collision::BoundingBox objectBB;
			o->setPosition(object->position);
			objectBB.size = (Vector2f)o->getTileSize();
			objectBB.position = (Point2f)o->getPosition() + (Vector2f)movement;
			if (objectBB.position.x + objectBB.size.x > 0 && objectBB.position.y + objectBB.size.y > 0) {
				o->setTileIndex(object->spriteIndex);
				o->setPosition(Point2i(objectBB.position));
				o->setTileSize(o->getTileSize());
				o->render();
			}
		}
	}
}

std::vector<ObjectMap::ObjectFake*>* ObjectMap::getObjectList() const {
	return objectList;
}
Core::Collision::BoundingBox ObjectMap::getBoundingBox(ObjectFake* o) {
	Core::Collision::BoundingBox b;
	Object* _o = ObjectManager::getObject(o->id);
	b.position = Point2f(static_cast<float>(o->position.x), static_cast<float>(o->position.y));
	b.size = static_cast<Vector2f>(_o->getTileSize());
	return b;
}