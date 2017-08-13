//
//  ItemMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "ItemMap.h"

using namespace Adventure;
using Core::Collision;

std::string ItemMap::relativePath = "";

ItemMap::ItemMap() {
	itemList = new std::vector<ItemFake*>();
}
ItemMap::ItemMap(const std::string& path) {
	itemList = new std::vector<ItemFake*>();
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
	else {
		loadPath = path;
	}
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif

	FILE* f;
	if (!fopen_s(&f, loadPath.c_str(), "rb")) {
		throw std::runtime_error("[Item Map] Impossible to load file: " + loadPath);
	}
	fread(&size, sizeof(int), 1, f);
	for (int x = 0; x < size; x++) {
		ItemFake *i = new ItemFake;
		fread(&i->id, sizeof(int), 1, f);
		fread(&i->position, sizeof(Point2i), 1, f);
		i->spriteIndex = sf::Point2i(0, 0);
		itemList->push_back(i);
	}
	fclose(f);
}
ItemMap::~ItemMap() {
	if (itemList != nullptr) {
#ifndef _WIN32
		for_each(itemList->begin(), itemList->end(), default_delete<ItemFake>());
#else
		for_each(itemList->begin(), itemList->end(),
			[](ItemFake* itf) {
			delete itf;
		});
#endif
		delete itemList;
		itemList = nullptr;
	}
}
void ItemMap::setSpriteIndex(size_t index, Point2i spriteIndex) {
	if (index >= itemList->size()) {
		throw std::runtime_error("[Item Map] There is not an object at the specified index");
	}
	itemList->at(index)->spriteIndex = spriteIndex;

}
void ItemMap::setSpriteIndex(size_t index, int spriteIndexX, int spriteIndexY) {
	setSpriteIndex(index, Point2i(spriteIndexX, spriteIndexY));
}
Point2i ItemMap::getSpriteIndex(size_t index) const {
	if (index >= itemList->size()) {
		throw std::runtime_error("[Item Map] There is not an object at the specified index");
	}
	return itemList->at(index)->spriteIndex;
}
int ItemMap::getSpriteIndexX(size_t index) const {
	if (index >= itemList->size()) {
		throw std::runtime_error("[Item Map] There is not an object at the specified index");
	}
	return itemList->at(index)->spriteIndex.x;
}

int ItemMap::getSpriteIndexY(size_t index) const {
	if (index >= itemList->size()) {
		throw std::runtime_error("[Item Map] There is not an object at the specified index");
	}
	return itemList->at(index)->spriteIndex.y;
}
void ItemMap::addItem(int id, Point2i position) {
	this->itemList->emplace_back(new ItemFake(id, position, Point2i(0, 0)));
}
void ItemMap::removeItem(size_t index) {
	if (index < itemList->size()) {
		itemList->at(index) = nullptr;
	}
}
void ItemMap::render(int x, int y, int width, int height) {
	render(Point2i(x, y), Vector2i(width, height));
}
void ItemMap::render(Point2i position, Vector2i size) {
	Point2i renderPosition;
	for (auto const& item : *itemList) {
		Item* i = ItemManager::getItem(item->id);
		if (i != nullptr) {
			//Here i check if my item collides with the area, if so it means it is on the visible area
			//Item Bounding box
			Core::Collision::BoundingBox itemBB;
			i->setPosition(item->position);
			itemBB.size = (Vector2f)i->getTileSize();
			itemBB.position = (Point2f)i->getPosition();
			if (itemBB.position.x + itemBB.size.x > 0 && itemBB.position.y + itemBB.size.y > 0) {
				i->setPosition(Point2i(itemBB.position));
				i->setTileSize(i->getTileSize());
				i->render();
			}
		}
	}
}
void ItemMap::renderPerfect(int x, int y, int width, int height, int moveX, int moveY) {
	renderPerfect(Point2i(x, y), Vector2i(width, height), Vector2i(moveX, moveY));
}
void ItemMap::renderPerfect(Point2i position, Vector2i size, Vector2i movement) {
	Point2i renderPosition;
	for (auto const& item : *itemList) {
		Item* i = ItemManager::getItem(item->id);
		if (i != nullptr) {
			//Here i check if my item collides with the area, if so it means it is on the visible area
			//Item Bounding box
			Core::Collision::BoundingBox itemBB;
			i->setPosition(item->position);
			itemBB.size = (Vector2f)i->getTileSize();
			itemBB.position = (Point2f)i->getPosition() + (Vector2f)movement;
			if (itemBB.position.x + itemBB.size.x > 0 && itemBB.position.y + itemBB.size.y > 0) {
				i->setPosition(Point2i(itemBB.position) + position);
				i->setTileSize(i->getTileSize());
				i->render();
			}
		}
	}
}

std::vector<ItemMap::ItemFake*>* ItemMap::getItemList() const {
	return this->itemList;
}
Core::Collision::BoundingBox ItemMap::getBoundingBox(ItemFake* i) const {
	Core::Collision::BoundingBox b;
	Item* _i = ItemManager::getItem(i->id);
	b.position = Point2f(static_cast<float>(i->position.x), static_cast<float>(i->position.y));
	b.size = (Vector2f)_i->getTileSize();
	return b;
}