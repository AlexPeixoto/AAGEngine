//
//  Collision.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/1/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Collision.h"

using namespace Core;
using sf::Point2i;

bool Collision::collidedAABB(BoundingBox b1, BoundingBox b2) {
	if (b1.position.x + b1.size.x < b2.position.x || b1.position.x > b2.position.x + b2.size.x)return false;
	if (b1.position.y + b1.size.y < b2.position.y || b1.position.y > b2.position.y + b2.size.y)return false;
	return true;
}
Point2i Collision::penetrationAABB(BoundingBox b1, BoundingBox b2) {
	Point2i penetration;
	penetration.x = penetration.y = 0;
	if (!collidedAABB(b1, b2)) {
		return penetration;
	}
	else {
		penetration.x = static_cast<int>(b1.position.x + b1.size.x - b2.position.x);
		penetration.y = static_cast<int>(b1.position.y + b1.size.y - b2.position.y);
	}
	return penetration;
}

/*
 *
 * Code from SFML Simple Collision Detection
 * https://github.com/LaurentGomila/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
 *
 */
void Collision::getSpriteAxis(Adventure::Sprite* sprite, Point2f* axis) {
	sf::Transform trans = sprite->getSfSprite()->getTransform();
	sf::IntRect local = sprite->getSfSprite()->getTextureRect();
	axis[0] = (Point2f)trans.transformPoint(0.f, 0.f);
	axis[1] = (Point2f)trans.transformPoint(static_cast<float>(local.width), 0.f);
	axis[2] = (Point2f)trans.transformPoint(static_cast<float>(local.width), static_cast<float>(local.height));
	axis[3] = (Point2f)trans.transformPoint(0.f, static_cast<float>(local.height));
}
void Collision::getImageAxis(Core::Image* image, Point2f* axis) {
	sf::Transform trans = image->getSfSprite()->getTransform();
	sf::IntRect local = image->getSfSprite()->getTextureRect();
	axis[0] = (Point2f)trans.transformPoint(0.f, 0.f);
	axis[1] = (Point2f)trans.transformPoint(static_cast<float>(local.width), 0.f);
	axis[2] = (Point2f)trans.transformPoint(static_cast<float>(local.width), static_cast<float>(local.height));
	axis[3] = (Point2f)trans.transformPoint(0.f, static_cast<float>(local.height));
}
void Collision::projectOntoAxis(Point2f points[4], const sf::Vector2f& axis, float& min, float& max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
{
	min = points[0].x*axis.x + points[0].y*axis.y;
	max = min;
	for (int j = 1; j < 4; j++)
	{
		float projection = points[j].x*axis.x + points[j].y*axis.y;

		if (projection < min) {
			min = projection;
		}
		if (projection > max) {
			max = projection;
		}
	}
}
bool Collision::collidedOBB(Point2f axesBox1[4], Point2f axesBox2[4]) {
	sf::Vector2f axes[4] = {
		sf::Vector2f(axesBox1[1].x - axesBox1[0].x,
					  axesBox1[1].y - axesBox1[0].y),
		sf::Vector2f(axesBox1[1].x - axesBox1[2].x,
					  axesBox1[1].y - axesBox1[2].y),
		sf::Vector2f(axesBox2[0].x - axesBox2[3].x,
					  axesBox2[0].y - axesBox2[3].y),
		sf::Vector2f(axesBox2[0].x - axesBox2[1].x,
					  axesBox2[0].y - axesBox2[1].y)
	};
	for (int i = 0; i < 4; ++i)
	{
		float minOBB1, maxOBB1, minOBB2, maxOBB2;

		projectOntoAxis(axesBox1, axes[i], minOBB1, maxOBB1);
		projectOntoAxis(axesBox2, axes[i], minOBB2, maxOBB2);
		if (!((minOBB2 <= maxOBB1) && (maxOBB2 >= minOBB1))) {
			return false;
		}
	}
	return true;
}
Point2i Collision::penetrationOBB(Point2f axesBox1[4], Point2f axesBox2[4]) {
	sf::Vector2f axes[4] = {
		sf::Vector2f(axesBox1[1].x - axesBox1[0].x,
					  axesBox1[1].y - axesBox1[0].y),
		sf::Vector2f(axesBox1[1].x - axesBox1[2].x,
					  axesBox1[1].y - axesBox1[2].y),
		sf::Vector2f(axesBox2[0].x - axesBox2[3].x,
					  axesBox2[0].y - axesBox2[3].y),
		sf::Vector2f(axesBox2[0].x - axesBox2[1].x,
					  axesBox2[0].y - axesBox2[1].y)
	};
	int penetrationX = 0;
	int penetrationY = 0;
	for (int i = 0; i < 4; i++)
	{
		float minOBB1, maxOBB1, minOBB2, maxOBB2;

		projectOntoAxis(axesBox1, axes[i], minOBB1, maxOBB1);
		projectOntoAxis(axesBox2, axes[i], minOBB2, maxOBB2);
		if (((minOBB2 <= maxOBB1) && (maxOBB2 >= minOBB1))) {
			if (i == 0 || i == 2) {
				if (maxOBB1 - minOBB2 > penetrationX) {
					penetrationX = static_cast<int>(maxOBB1 - minOBB2);
				}
			}
			if (i == 1 || i == 3) {
				if (maxOBB1 - minOBB2 > penetrationY) {
					penetrationY = static_cast<int>(maxOBB1 - minOBB2);
				}
			}
		}
	}
	return Point2i(penetrationX, penetrationY);
}