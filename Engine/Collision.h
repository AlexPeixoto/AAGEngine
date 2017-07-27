//
//  Collision.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/1/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Collision__
#define __Action_Adventure_Game_Engine__Collision__

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "Point.h"
#include "Image.h"

using sf::Point2i;
using sf::Point2f;
using sf::Vector2i;
using sf::Vector2f;

namespace Core{
    class Collision{
    private:
        //Here i write the functions for OBB
      //  static vector<Point2i> returnAxis(Sprite* s);
        static void projectOntoAxis (Point2f points[4], const sf::Vector2f& axis, float& min, float& max) ;
    public:
        typedef struct BoundingBox{
            Point2f position;
            Vector2f size;
        } BoundingBox;
        
        static void getSpriteAxis(Adventure::Sprite* sprite, Point2f* axis);
        static void getImageAxis(Core::Image* image, Point2f* axis);
        
        static bool collidedAABB(BoundingBox b1, BoundingBox b2);
        static Point2i penetrationAABB(BoundingBox b1, BoundingBox b2);
        
        static bool collidedOBB(Point2f axesBox1[4], Point2f axesBox2[4]);
        static Point2i penetrationOBB(Point2f axesBox1[4], Point2f axesBox2[4]);
        
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Collision__) */
