//
//  ObjectManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ObjectManager.h"

using namespace Adventure;

std::vector<Object*> *ObjectManager::objectList = new std::vector<Object*>();
std::string ObjectManager::relativePath = "";

ObjectManager::~ObjectManager() {
	if (objectList != nullptr) {
#ifndef _WIN32
		std::for_each(objectList->begin(), objectList->end(), default_delete<Object>());
#else
		std::for_each(objectList->begin(), objectList->end(),
			[](Object* o) {
			delete o;
		});
#endif
		delete objectList;
		objectList = nullptr;
	}
}

void ObjectManager::render(size_t id, Point2i position) {
	for (const auto& object : *objectList)
		if (object->id == id) {
			if (object->objectSprite == nullptr) {
				object->loadSprite();
				object->setPosition(position);
			}
			object->render();
		}
}

Object* ObjectManager::getObject(size_t id) {
	for (const auto& object : *objectList)
		if (object->id == id)
			return object;
	return nullptr;
}
bool ObjectManager::loadSprite(size_t id) {
	for (const auto& object : *objectList)
		if (object->id == id) {
			object->loadSprite();
			return true;
		}
	return false;
}

bool ObjectManager::checkIfExists(size_t id) {
	for (const auto& object : *objectList)
		if (object->id == id)
			return true;
	return false;
}

//Need to check first if that item exists
bool ObjectManager::loadFromFile(const std::string& path) {
	std::string loadPath;
	if (relativePath.size() > 0) {
		size_t lastIndex = path.find_last_of("/");
		if (lastIndex != std::string::npos)
			//if path have the / on the end
			loadPath = path[path.size() - 1] == '/' ? relativePath + path.substr(lastIndex + 1) : relativePath + "/" + path.substr(lastIndex + 1);
		else
			loadPath = path[path.size() - 1] == '/' ? relativePath + path : relativePath + "/" + path;
	}
	else
		loadPath = path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif

	FILE* f;
	if (!fopen_s(&f, loadPath.c_str(), "rb")) {
		throw std::runtime_error("[Object Manager] Could not open: " + loadPath);
		return false;
	}
	Object* o = nullptr;
	bool skipLater = false;
	int size = 0;
	int id = -1;
	char _path[255], name[100];
	//Read how many itens i have stored in the file
	fread(&size, sizeof(int), 1, f);
	for (int x = 0; x < size; x++) {

		skipLater = false;
		fread(&id, sizeof(int), 1, f);

		//IF ALREADY INSERTED SKIP IT
		if (checkIfExists(id) == true) {
			Debug::LogManager::log(Debug::LogLevel::WARNING, "[Object Manager] Skiping object on loadFromFile with id: %T", id);
			//read all the data, then delete it on the end
			skipLater = true;
		}
		ObjectManager::objectList->push_back(new Object());
		o = ObjectManager::objectList->at(ObjectManager::objectList->size() - 1);
		if (o == nullptr || o == NULL)break;
		o->id = id;
		fread(&o->tileSize.x, sizeof(int), 1, f);
		fread(&o->tileSize.y, sizeof(int), 1, f);

		fread(_path, sizeof(char), 255, f);
		o->path = std::string(_path);

		fread(name, sizeof(char), 100, f);
		o->name = std::string(name);

		fread(&o->randomize, sizeof(bool), 1, f);
		int pSize;
		fread(&pSize, sizeof(int), 1, f);
		for (int y = 0; y < pSize; y++) {
			//I will write the key string size + 1  \0 terminator
			int kSize;
			fread(&kSize, sizeof(int), 1, f);

			char* kChar = new char[kSize];
			//Now i will write THE key
			fread(kChar, sizeof(char), kSize, f);


			int vSize;
			//I will write the value string size + 1  \0 terminator
			fread(&vSize, sizeof(int), 1, f);

			char* kValue = new char[vSize];

			//Now i will write THE value
			fread(kValue, sizeof(char), vSize, f);

			if (o->properties->find(std::string(kChar)) != o->properties->end()) {
				Debug::LogManager::log(Debug::LogLevel::WARNING, "[Object Manager]Skiping object property on loadFromFile with objectId: %T and propertyKey: %T", id, kChar);
				continue;
			}

			o->properties->insert(std::make_pair(std::string(kChar), std::string(kValue)));
		}
		int iSize, itemId, itemQuantity;
		fread(&iSize, sizeof(int), 1, f);
		for (int y = 0; y < iSize; y++) {
			fread(&itemId, sizeof(int), 1, f);
			fread(&itemQuantity, sizeof(int), 1, f);
			if (o->items->find(id) != o->items->end()) {
				Debug::LogManager::log(Debug::LogLevel::WARNING, "[Object Manager]Skiping object item on loadFromFile with objectId: %T and itemId: %T", id, itemId);
				continue;
			}
			o->items->insert(std::make_pair(itemId, itemQuantity));
		}

		if (skipLater) {
			//if the data already exists i delete all the data inserted
			o->properties->clear();
			o->items->clear();
			ObjectManager::objectList->pop_back();
			skipLater = false;
		}
	}
	fclose(f);
	return true;
}
void ObjectManager::unloadData() {
	for (int x = 0; x < objectList->size(); x++)
		delete objectList->at(x);
	objectList->clear();
}
bool ObjectManager::addObject(Object* object) {
	if (ObjectManager::getObject(object->id))return false;
	ObjectManager::objectList->push_back(object);
	return true;
}
bool ObjectManager::addObject(size_t id, const std::string& path, const std::string& name, Vector2i tileSize, bool randomize) {
	if (ObjectManager::getObject(id)) {
		return false;
	}
	else {
		Object* o = new Object(static_cast<int>(id), path, name, tileSize, randomize);
		ObjectManager::objectList->push_back(o);
		return true;
	}
}
bool ObjectManager::removeObject(size_t id) {
	for (auto i = ObjectManager::objectList->begin(); i != ObjectManager::objectList->end(); i++)
		if ((*i)->id == id) {
			ObjectManager::objectList->erase(i);
			return true;
		}
	return false;
}
size_t ObjectManager::getRandomItem(size_t id) {
	Object* o = getObject(id);
	//Load all the ids inside a vector
	std::vector<int> ids;
	for (auto i = o->items->begin(); i != o->items->end(); i++)
		ids.push_back(i->first);

	size_t max = o->items->size() - 1;
	// Seed with a real random value, if available
	std::random_device rd;

	std::default_random_engine e1(rd());
	std::uniform_int_distribution<size_t> uniform_dist(0, max);
	size_t index = uniform_dist(e1);
	return o->items->at(ids.at(index));
}