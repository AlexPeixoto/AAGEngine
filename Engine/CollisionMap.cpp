//
//  CollisionMap.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/8/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "CollisionMap.h"

using namespace Adventure;

std::string CollisionMap::relativePath = "";

CollisionMap::CollisionMap() {
	collisionStructure = nullptr;
	collisionData = nullptr;
}
CollisionMap::~CollisionMap() {
	if (collisionData != nullptr) {
		delete collisionData;
		collisionData = nullptr;
	}
	if (collisionStructure != nullptr) {
		delete collisionStructure;
		collisionStructure = nullptr;
	}

}
CollisionMap::CollisionMap(const std::string& path) {
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
		throw std::runtime_error("[Collision Map] Could not open: " + loadPath);
	}
	collisionStructure = new CollisionStructure;
	fread(collisionStructure, sizeof(CollisionStructure), 1, f);
	collisionData = new int16_t[collisionStructure->tileBlock.x*collisionStructure->tileBlock.y];
	fread(collisionData, sizeof(int16_t), collisionStructure->tileBlock.x*collisionStructure->tileBlock.y, f);
	fclose(f);
}

bool CollisionMap::collided(Core::Collision::BoundingBox b, Vector2f movement) {
	//Get player/object position, convert to tile size and check if on that tile have a collision
	/*
	 * I use the player position
	 * The Map Manager provides the camera movement, so if the camera moves the collision detection is compensated
	 * Needs to inverse the movement, because the movement to the right "pulls back" all the content on the matrix.
	 ** It means, if i move my player to the right i need to move all the content to the left, so the movement is inversed.
	 ** But to analise the collision matrix i need to inverse it again, because i use real index.
	 */
	Point2i limit;
	limit.y = static_cast<int>((b.position.y + b.size.y - movement.y) / collisionStructure->tileSize.y);
	limit.x = static_cast<int>((b.position.x + b.size.x - movement.x) / collisionStructure->tileSize.x);

	for (int y = static_cast<int>(b.position.y - movement.y) / collisionStructure->tileSize.y; y <= limit.y; y++) {
		for (int x = static_cast<int>(b.position.x - movement.x) / collisionStructure->tileSize.x; x <= limit.x; x++) {
			if (x < 0 || y < 0) {
				continue;
			}
			else if (collisionData[x + (y*collisionStructure->tileBlock.x)] > -1) {
				return true;
			}
		}
	}
	return false;
}

bool CollisionMap::collided(Point2i location) {
	return (collisionData[(location.x / collisionStructure->tileSize.x) +
		(location.y / collisionStructure->tileSize.y)*collisionStructure->tileBlock.x]) > -1;
}
int CollisionMap::getValue(int x, int y) {
	Point2i position;
	position.x = x;
	position.y = y;
	return getValue(position);

}
int CollisionMap::getValue(Point2i position) {
	if (position.x > collisionStructure->tileBlock.x || position.y > collisionStructure->tileBlock.y) {
		std::stringstream ss;
		ss.str("");
		ss << "Position X=>" << position.x << " Y=>" << position.y << " is out of bounds" << std::endl;
		throw std::runtime_error(ss.str());
	}
	else {
		return collisionData[position.x + position.y*collisionStructure->tileBlock.x];
	}
}
void CollisionMap::setValue(int x, int y, int value) {
	Point2i position;
	position.x = x;
	position.y = y;
	setValue(position, value);
}
void CollisionMap::setValue(Point2i position, int value) {
	if (position.x > collisionStructure->tileBlock.x || position.y > collisionStructure->tileBlock.y) {
		std::stringstream ss("");
		ss << "Position X=>" << position.x << " Y=>" << position.y << " is out of bounds" << std::endl;
		throw std::runtime_error(ss.str());
	}
	else {
		collisionData[position.x + position.y*collisionStructure->tileBlock.x] = value;
	}
}

