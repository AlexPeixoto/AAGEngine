//
//  Game.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 1/20/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Game.h"

using namespace Core;

sf::RenderWindow *Game::window = nullptr;
sf::Event Game::event;
sf::Time Game::deltaTime;
float Game::_deltaTime;
Game::Game(std::function<void(int, char**)> init, int argc, char** argv){
    // Initialize default structure
    sf::ContextSettings set;
    set.depthBits=24;
    set.stencilBits=0;
    set.antialiasingLevel=4;
    set.majorVersion=2;
    set.minorVersion=0;
    // Here the window should be initialized
    init(argc, argv);
    initRenderFunc=initProcessFunc=false;
}
Game::Game(int width, int height, int framerate, std::string title, int argc, char** argv){
    sf::ContextSettings set;
    set.depthBits=24;
    set.stencilBits=0;
    set.antialiasingLevel=4;
    set.majorVersion=2;
    set.minorVersion=0;
    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default);
    if(framerate<=0)
        window->setVerticalSyncEnabled(true);
    else
        window->setFramerateLimit(framerate);
    this->getParams(argc, argv);
    initRenderFunc=initProcessFunc=false;
}
void Game::resize(int width, int height){
	View mgv = View(sf::FloatRect(0.f, 0.f, (float)width, (float)height));
    window->setView(mgv);
}
Game::~Game(){

}
void Game::getParams(int argc, char** argv){}
void Game::process(){}
void Game::render(){}
void Game::setDeltaTime(){
    Game::_deltaTime=Game::deltaTime.asSeconds();
}
 
float Game::getDeltaTimef(){
    return Game::_deltaTime;
}
void Game::setProcess(std::function<void()> processFunc){
    initProcessFunc=true;
    this->processFunc=processFunc;
}
void Game::setRender(std::function<void()> renderFunc){
    initRenderFunc=true;
    this->renderFunc=renderFunc;
}
void Game::run(){
    // Here i bind to the functions if the functors are not initialized, so i dont have an if inside the while for render and process
    if(!initRenderFunc)
        this->renderFunc=std::bind(&Game::render, this);
    if(!initProcessFunc)
        this->processFunc=std::bind(&Game::process, this);
    // Start the game loop
    while (window->isOpen())
    {
        Game::deltaTime = deltaClock.restart();
        // Process events
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window->close();
            else if(event.type == sf::Event::Resized)
                resize(event.size.width, event.size.height);
        }
        window->clear();
        InputControl::updateStates();
        this->renderFunc();
        this->processFunc();
        window->display();
   
    }
}
