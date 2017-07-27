//
//  Image.cpp
//  OpenGL Window
//
//  Created by Alex Peixoto on 11/22/13.
//  Copyright (c) 2013 Alex Peixoto. All rights reserved.
//

#include "Image.h"
#include "Game.h"
using namespace Core;
using std::stringstream;

RenderWindow * Image::window = nullptr;
string Image::relativePath="";

Image::Image(string path){
    string loadPath;
    if(relativePath.size()>0){
        size_t lastIndex=path.find_last_of("/");
        if(lastIndex!=string::npos)
            //if path have the / on the end
            loadPath=path[path.size()-1]=='/' ? relativePath+path.substr(lastIndex+1) : relativePath+"/"+path.substr(lastIndex+1);
        else
            loadPath=path[path.size()-1]=='/' ? relativePath+path : relativePath+"/"+path;
    }
    else
        loadPath=path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
    this->path=loadPath;
    texture = new sf::Texture();
    if(!texture->loadFromFile(loadPath)){
        throw std::runtime_error("[Image] Impossible to load file: " + loadPath);
    }
    sprite = new sf::Sprite(*texture);
    frameSize=Vector2f(1.0f, 1.0f);
    textureSize=texture->getSize();
    rotation=0;
    reloading=false;
}
Image::~Image(){
    delete texture;
    delete sprite;
}
void Image::setWindow(sf::RenderWindow *window){
    Image::window=window;
}
void Image::changeImage(string path){
    reloading=true;
    if(sprite!=nullptr){
        delete sprite;
        sprite=nullptr;
    }
    if(texture!=nullptr){
        delete texture;
        texture=nullptr;
    }
    Image::Image(path.c_str());
}
int Image::getHeight(){
    return textureSize.y;
}
int Image::getWidth(){
    return textureSize.x;
}
float Image::getRotation(){
    return rotation;
}
Vector2<unsigned> Image::getSize(){
    return textureSize;
}
void Image::setScale(Vector2f scale){
    frameSize=scale;
}
void Image::setHeightScale(float height){
    //The height in px
    frameSize.y=height;
}
void Image::setWidthScale(float width){
    //The height in px
    frameSize.x=width;
}
float Image::getWidthScale(){
    return frameSize.x;
}
float Image::getHeightScale(){
    return frameSize.y;
}
Vector2f Image::getScale(){
    return frameSize;
}
void Image::setX(int x){
    framePos.x=x;
}
void Image::setY(int y){
    framePos.y=y;
}
int Image::getX(){
    return framePos.x;
}
int Image::getY(){
    return framePos.y;
}
Point2i Image::getPosition(){
    return framePos;
}
void Image::setPosition(Point2i position){
    setX(position.x);
    setY(position.y);
}
void Image::setRotation(float rotation){
    this->rotation=rotation;
    sprite->setRotation(rotation);
}
void Image::setOrigin(Point2i origin){
    this->origin=origin;
    sprite->setOrigin(origin.x, origin.y);
}
Point2i Image::getOrigin(){
    return origin;
}
string Image::getPath() const{
    return path;
}
void Image::render(){
    if(reloading || Image::window==nullptr)return;
    sprite->setPosition(framePos.x, framePos.y);
    sprite->setScale(frameSize.x, frameSize.y);
    window->draw(*sprite);
}
void Image::renderSub(Point2f position, Vector2f size){
    renderSub(position.x, position.y, size.x, size.y);
}
void Image::renderSub(float x, float y, float width, float height){
    if(reloading || Image::window==nullptr)return;
    this->sprite->setScale(this->frameSize.x, this->frameSize.y);
    this->sprite->setTextureRect(sf::IntRect(x, y, width, height));
    this->sprite->setPosition(this->framePos.x, this->framePos.y);
    Image::window->draw(*this->sprite);
}
sf::Sprite* Image::getSfSprite(){
    return sprite;
}
sf::Texture* Image::getSfTexture(){
    return texture;
}