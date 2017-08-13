//
//  Point.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/1/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef OpenGL_Game_Engine_Point_h
#define OpenGL_Game_Engine_Point_h
#include <iostream>
#include <SFML/System/Vector2.hpp>


namespace sf{
    //! Implementa classe Point2<Template>
    template<typename T> class Point2: public Vector2<T>{
    public:
        Point2();
        Point2(T X, T Y);
        Point2& operator=(const Point2<T> &source);
        Point2& operator=(const Vector2<T> &source);
        
        template <typename U>
        explicit Point2(const Point2<U>& point);
        
        template <typename U>
        explicit Point2(const Vector2<U>& point);
    };
    typedef sf::Point2<float> Point2f;
    typedef sf::Point2<int> Point2i;
    typedef sf::Point2<unsigned int> Point2u;
    
    template<typename T>
    inline Point2<T>::Point2():Vector2<T>(0, 0){}
    
    template<typename T>
    inline Point2<T>::Point2(T X, T Y):Vector2<T>(X, Y){}
    
    template <typename T>
    template <typename U>
    inline Point2<T>::Point2(const Point2<U>& point)
    {
        Vector2<T>::x=static_cast<T>(point.x);
        Vector2<T>::y=static_cast<T>(point.y);
    }
    
    template <typename T>
    template <typename U>
    inline Point2<T>::Point2(const Vector2<U>& point)
    {
        Vector2<T>::x=static_cast<T>(point.x);
        Vector2<T>::y=static_cast<T>(point.y);
    }

    
    template<typename T>
    Point2<T>& Point2<T>::operator=(const Point2<T> &source){
        this->x = source.x;
        this->y = source.y;
        return *this;
    }
    template<typename T>
    Point2<T>& Point2<T>::operator=(const Vector2<T> &source){
        this->x = source.x;
        this->y = source.y;
        return *this;
    }

    
    template <typename T>
    inline Point2<T> operator -(const Point2<T>& right)
    {
        return Vector2<T>(-right.x, -right.y);
    }
    
    template <typename T>
    inline Point2<T> operator +(const Point2<T>& left, const Vector2<T>& right)
    {
        return Point2<T>(left.x + right.x, left.y + right.y);
    }
    
    
    template <typename T>
    inline Point2<T> operator -(const Point2<T>& left, const Vector2<T>& right)
    {
        return Point2<T>(left.x - right.x, left.y - right.y);
    }
    
    
    template <typename T>
    inline Point2<T> operator *(const Point2<T>& left, T right)
    {
        return Point2<T>(left.x * right, left.y * right);
    }
    
    
    template <typename T>
    inline Point2<T> operator *(T left, const Point2<T>& right)
    {
        return Point2<T>(right.x * left, right.y * left);
    }
    
    
    template <typename T>
    inline Point2<T> operator /(const Point2<T>& left, T right)
    {
        return Point2<T>(left.x / right, left.y / right);
    }
    
    template <typename T>
    inline bool operator ==(const Point2<T>& left, const Point2<T>& right)
    {
        return (left.x == right.x) && (left.y == right.y);
    }
    
    template <typename T>
    inline bool operator !=(const Point2<T>& left, const Point2<T>& right)
    {
        return (left.x != right.x) || (left.y != right.y);
    }

}
#endif
