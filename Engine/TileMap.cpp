//
//  TileMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 1/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//
/*
 *NOTES:
 * 1- IMPOSSIBLE TO SCALE TILES
 */

#include "TileMap.h"
#include <cstring>

using namespace Adventure;

std::string TileMap::relativePath = "";

TileMap::TileMap() {
	tileData = nullptr;
	tileHeader = nullptr;
	tileImage = nullptr;
}
TileMap::TileMap(const std::string& path)
{
	loadLevel(path);
	loadTiles();
}
TileMap::~TileMap()
{
	delete tileData;
	delete tileHeader;
	tileData = nullptr;
	tileHeader = nullptr;
		
}

void TileMap::loadTiles()
{
	tileImage = new Core::Image(tileHeader->filename);
}

void TileMap::initializeData(Vector2<int> tileBlock, Vector2<int> tileSize, const std::string& path) {

	delete tileHeader;
	delete tileData;
	delete tileImage;

	tileData = (int16_t*)malloc(sizeof(int16_t)*tileHeader->tileBlock.x*tileHeader->tileBlock.y);
	tileImage = new Core::Image(path);
	tileHeader = new TileStructure;

	tileHeader->tileBlock = tileBlock;
	tileHeader->tileSize = tileSize;
	#ifdef _WIN32
		strcpy_s(tileHeader->filename, path.c_str());
	#else
		strcpy(tileHeader->filename, path.c_str());
	#endif

	std::memset(&tileData, 0, sizeof(tileData));	
}
void TileMap::initializeData(int tileBlockX, int tileBlockY, int tileSizeX, int tileSizeY, const std::string& path) {
	Vector2i tileBlock, tileSize;
	tileBlock.x = tileBlockX;
	tileBlock.y = tileBlockY;
	tileSize.x = tileSizeX;
	tileSize.y = tileSizeY;
	initializeData(tileBlock, tileSize, path);
}
void TileMap::addTile(int x, int y, int16_t value) {
	tileData[y*tileHeader->tileBlock.x + x] = value;
}
void TileMap::clearDataStructure() {
	std::memset(&tileHeader, sizeof(tileHeader), 0);
}
void TileMap::clearData() {
	std::memset(&tileData, sizeof(int16_t), tileHeader->tileBlock.x*tileHeader->tileBlock.y);
}
void TileMap::clear() {
	clearData();
	clearDataStructure();
}
void TileMap::loadLevel(const std::string& path)
{
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
	FILE* f;
	const std::string throwMessage = "[Tile Map] Impossible to load file: " + loadPath;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
	if (!fopen_s(&f, loadPath.c_str(), "rb")) {
		throw std::runtime_error(throwMessage);
	}
#else
	f = fopen(loadPath.c_str(), "rb");
	if (!f) {
		throw std::runtime_error(throwMessage);
	}
#endif

	tileHeader = new TileStructure;
	fread(&(tileHeader->tileBlock), sizeof(int), 2, f);
	fread(&(tileHeader->tileSize), sizeof(int), 2, f);
	fread(&(tileHeader->filename), sizeof(char), 256, f);
	tileData = (int16_t*)malloc(sizeof(int16_t)*tileHeader->tileBlock.x*tileHeader->tileBlock.y);
	fread(tileData, sizeof(int16_t), tileHeader->tileBlock.x*tileHeader->tileBlock.y, f);
	fclose(f);
}
Vector2i TileMap::getSize() {
	Vector2i mapSize;
	mapSize.x = tileHeader->tileSize.x * tileHeader->tileBlock.x;
	mapSize.y = tileHeader->tileSize.y * tileHeader->tileBlock.y;
	return mapSize;
}
Vector2i TileMap::getTileSize() const {
	return tileHeader->tileSize;
}
Vector2i TileMap::getTileNumber() const {
	return tileHeader->tileBlock;
}
Core::Image* TileMap::getImage() const {
	return tileImage;
}
void TileMap::render(Point2i position, Vector2i size) {
	render(position.x, position.y, size.x, size.y);
}
//change to position
void TileMap::render(int x, int y, int width, int height)
{
	int16_t imageValue;
	Vector2i blockPosition, imageSize;
	imageSize.x = tileImage->getWidth();
	imageSize.y = tileImage->getHeight();
	tileImage->setWidthScale(1);
	tileImage->setHeightScale(1);
	for (blockPosition.y = y; blockPosition.y < y + ceil(height / tileHeader->tileSize.y) + 1 && blockPosition.y < tileHeader->tileBlock.y; blockPosition.y++) {
		for (blockPosition.x = x; blockPosition.x < x + ceil(width / tileHeader->tileSize.x) && blockPosition.x < tileHeader->tileBlock.x; blockPosition.x++) {
			imageValue = tileData[(blockPosition.y*tileHeader->tileBlock.x) + blockPosition.x];
			if (imageValue != -1) {
				tileImage->setX(blockPosition.x*tileHeader->tileSize.x);
				tileImage->setY(blockPosition.y*tileHeader->tileSize.y);
				tileImage->renderSub(static_cast<float>(imageValue % (imageSize.x / tileHeader->tileSize.x)*tileHeader->tileSize.x),
					static_cast<float>(imageValue / (imageSize.x / tileHeader->tileSize.x)*tileHeader->tileSize.y),
					static_cast<float>(tileHeader->tileSize.x),
					static_cast<float>(tileHeader->tileSize.y));
			}
		}
	}
}
void TileMap::renderPerfect(Point2i position, Vector2i size, Vector2i movement) {
	renderPerfect(position.x, position.y, size.x, size.y, movement.x, movement.y);
}
//change to position
void TileMap::renderPerfect(int x, int y, int width, int height, int moveX, int moveY)
{
	int16_t imageValue;
	Vector2i blockPosition, imageSize;
	imageSize.x = tileImage->getWidth();
	imageSize.y = tileImage->getHeight();
	tileImage->setWidthScale(1);
	tileImage->setHeightScale(1);

	/* I begin the rendering from the position up to the number of tiles that can be rendered on one screen + my movement */
	/* I render until the point of my position +
	 * ceil(-(float)moveY/tileHeader->tileSize.y) <= the movement of the camera +
	 * ceil((float)height/tileHeader->tileSize.y) <= the height of the view area
	 */
	Point2i limit;
	limit.y = static_cast<int>(ceil(-(float)moveY / tileHeader->tileSize.y) + y + ceil((float)height / tileHeader->tileSize.y));
	limit.x = static_cast<int>(ceil(-(float)moveX / tileHeader->tileSize.y) + x + ceil(width / tileHeader->tileSize.x));
	for (blockPosition.y = y / imageSize.y; blockPosition.y < limit.y && blockPosition.y < tileHeader->tileBlock.y; blockPosition.y++) {
		for (blockPosition.x = x / imageSize.x; blockPosition.x < limit.x && blockPosition.x < tileHeader->tileBlock.x; blockPosition.x++) {
			imageValue = tileData[(blockPosition.y*tileHeader->tileBlock.x) + blockPosition.x];
			if (imageValue != -1) {
				tileImage->setX(blockPosition.x*tileHeader->tileSize.x + moveX + x);
				tileImage->setY(blockPosition.y*tileHeader->tileSize.y + moveY + y);
				tileImage->renderSub(static_cast<float>(imageValue % (imageSize.x / tileHeader->tileSize.x)*tileHeader->tileSize.x), //Module returns row
					static_cast<float>(imageValue / (imageSize.x / tileHeader->tileSize.x)*tileHeader->tileSize.y), //Int division returns the "line"
					static_cast<float>(tileHeader->tileSize.x),
					static_cast<float>(tileHeader->tileSize.y));
			}
		}
	}
}