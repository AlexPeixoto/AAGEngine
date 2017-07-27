//
//  Warp.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Warp.h"

using namespace Adventure;
Warp::Warp(){}
Warp::Warp(int id, string path, string name, int width, int height, int destinyX, int destinyY)
: id(id), path(path), name(name), size(Vector2i(width, height)), destiny(Point2i(destinyX, destinyY))
{}

Warp::Warp(int id, string path, string name, Vector2i size, Point2i destiny): id(id), path(path), name(name), size(size), destiny(destiny){}

Warp::~Warp(){}

void Warp::setPath(string path){
    this->path=path;
}
void Warp::setSize(int width, int height){
    size=Vector2i(width, height);
}
void Warp::setSize(Vector2i size){
    this->size=size;
}
void Warp::setDestiny(int x, int y){
    destiny=Point2i(x, y);
}
void Warp::setDestiny(Point2i destiny){
    this->destiny=destiny;
}
void Warp::setName(string name){
    this->name=name;
}

string Warp::getPath() const{
    return path;
}
string Warp::getName() const{
    return name;
}
Vector2i Warp::getSize(){
    return size;
}
Point2i Warp::getDestiny(){
    return destiny;
}
int Warp::getId(){
    return id;
}