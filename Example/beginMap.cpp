//
//  MainLevel.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "beginMap.h"
using Core::Collision;
using Core::Node;
using Core::Pathfind;
using Core::InputControl;


int BeginMap::mode=0;
bool BeginMap::renderText=true;
bool BeginMap::stopScript=false;

BeginMap::BeginMap(map<string, string> params):Level(){
    MyGame::loaded=0;
    textIndex=0;
    isthread=false;
    SoundEffectManager::unloadData();
    SoundEffectManager::loadFromFile("/Users/alexpeixoto/Desktop/sound.list");

    
    p=new Adventure::Player("/Developer/movement.png", 32, 64);
    
    Point2f playerPosition;
    
    t=new Core::TextControl("/Developer/times.ttf");
    
    d=new Dialog("/Developer/times.ttf");
    pf=nullptr;
    mapLevel="/Users/alexpeixoto/Documents/maps/beginMap.map";
    collisionLevel="/Users/alexpeixoto/Documents/maps/beginMap.map.collision";
    itemLevel="/Users/alexpeixoto/Documents/maps/beginMap.map.item";
    soundLevel="/Users/alexpeixoto/Documents/maps/beginMap.map.sound";
    objectLevel="/Users/alexpeixoto/Documents/maps/beginMap.map.object";
    warpLevel="/Users/alexpeixoto/Documents/maps/beginMap.map.warp";
    mapManager.loadTileLayer(mapLevel);
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadSoundMap(soundLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    

    WarpManager::loadFromFile("/Users/alexpeixoto/Desktop/beginMap.map.warpList");
    
    initData();
    
    if(params.find("position") != params.end()){
        if(params.at("position")=="outHouse"){
            //disable animation
            mode=1;
            playerPosition.x = 320;
            playerPosition.y = 140;
            p->updateDirection(Adventure::Character::Directions::DOWN, true);
            p->call();
        }
        else if(params.at("position")=="outTest"){
            playerPosition.x = 560;
            playerPosition.y = 170;
            mapManager.move(-400, 0);
            p->updateDirection(Adventure::Character::Directions::LEFT, true);
        }
        else if(params.at("position")=="outObject"){
            playerPosition.x = 290;
            playerPosition.y = 360;
            mapManager.move(0, -100);
            p->updateDirection(Adventure::Character::Directions::UP, true);
        }
        else{
            playerPosition.x = 150;
            playerPosition.y = 300;
            p->updateDirection(Adventure::Character::Directions::LEFT, true);
        }
    }
    else{
        playerPosition.x = 150;
        playerPosition.y = 300;
        p->updateDirection(Adventure::Character::Directions::LEFT, true);
    }
    
    p->setPosition(playerPosition);
    p->setLoop(true);
    p->setPixelsPerCall(150);
    p->resetLoopTo(3);
    p->setWidthScale(1);
    p->setHeightScale(1);
    p->setChangeOnCall(20);
    if(MyGame::oneCross==false){
        BackgroundMusic::intersectWith("/Users/alexpeixoto/Downloads/AF/beginmap.ogg", BackgroundMusic::IntersectMode::CROSS, 4);
        MyGame::oneCross=true;
    }

}
BeginMap::~BeginMap(){
    delete t;
    delete d;
    delete p;
    mapManager.getSoundMap()->getSounds()->at(0)->sound->stop();
    WarpManager::unloadData();
    SoundEffectManager::unloadData();
    if(pf!=nullptr)
        delete pf;
}
void BeginMap::initData(){
    
    TextTable::loadFromFile("/Users/alexpeixoto/Desktop/gametext.txt");
    
    //Dialog shapes
    speechBox=new Core::BackgroundShape();
    questionBox=new Core::BackgroundShape();;
    optionShape=new Core::BackgroundShape();
    speechBox->setBorderSize(1);
    questionBox->setBorderSize(1);
    optionShape->setBorderSize(1);
    
    speechBox->setBorderColor(10, 10, 10, 255);
    questionBox->setBorderColor(10, 10, 10, 255);
    optionShape->setBorderColor(20, 20, 20, 255);
    
    speechBox->setInsideColor(30, 30, 30, 120);
    questionBox->setInsideColor(30, 30, 30, 255);
    optionShape->setInsideColor(200, 40, 40, 255);
    
    _m = new Menu("/Developer/times.ttf");
    
    _p=new Adventure::Character("/Developer/movement.png", 32, 64);
    _p->setPosition(Point2f(90, 60));
    _p->setChangeOnCall(10);
    _p->setLoop(true);
    _p->resetLoopTo(3);
    generatePathForPlayer();
    if(mode!=1)
        _p->moveWithNodes(pfBeginNode, mapManager.getMovementPointer(), Vector2i(60, 60), Vector2i(15, 15), 30);
    
    t->setSpacing(5);
    t->setColor(255, 255, 255, 255);
    t->setScale(.5);
    t->splitInScreens(300, 100);
    
    
    //Handles the text when some event happens.
    messagePending=false;
    message="";
    
    //BackgroundMusic::loadSong("/Users/alexpeixoto/Downloads/AF/S0.ogg");
    //BackgroundMusic::play();
    //BackgroundMusic::intersectWith("/Users/alexpeixoto/Downloads/AF/S2.ogg", BackgroundMusic::IntersectMode::CROSS, 10);
    
    mapManager.getSoundMap()->playAll();
    mapManager.getSoundMap()->getSounds()->at(0)->sound->setVolume(100);
    
    d->setSpeechColor(255, 255, 255, 255);
    d->setDialogBoxSize(Vector2i(Game::window->getSize().x, 200));
    d->setDialogBoxPosition(Point2i(0, Game::window->getSize().y-202));
    d->setSpeechBoxShape(speechBox);
    
    d->setQuestionColor(255, 255, 255, 255);
    d->setQuestionBoxSize(Vector2i(150, 100));
    d->setQuestionBoxPosition(Point2i(0, Game::window->getSize().y-380));
    d->setQuestionBoxShape(questionBox);
    d->setOptionColor(255, 255, 255, 255);
    
    d->setQuestionBoxByLargest(true);
    
    d->setOptionInnerBorder(5);
    d->setOptionShape(optionShape);
    
    d->addSpeech(0, "Choose an number.", false);
    d->addSpeech(1, "Nice choice.", false);
    d->addSpeech(2, "Best one ever, good luck on your trip!", false);
    
    
    d->addQuestion(0, "Can you help me?", [=](int speechId, int questionId, int optionId, Dialog* dialog) -> void {
        //Disable the question render
        dialog->setRenderingQuestion(false);
        //go to first answer
        if(speechId==0 && questionId==0 && optionId==0)
            dialog->gotoSpeech(1);
        //go to the second answer
        else if(speechId==0 && questionId==0 && optionId>0)
            dialog->gotoSpeech(2);
        //go to the second answer
        
        mode=1;
    });
    
    d->addOption(0, 0, "1");
    d->addOption(0, 1, "2");
    d->addOption(0, 2, "3");
    d->addOption(0, 3, "4");
    d->addOption(0, 4, "5");

    //On the Speech 0 i have the question 0
    d->addDialogHandle(0, 0);
    
}
void BeginMap::generatePathForPlayer(int mode){
    if(pf==nullptr)
        pf=new Pathfind();
    else
        pf->deleteNodeContent();
    int limit=50*50;
    int* movementMap=new int[limit];
    
    for(int x=0;x<limit;x++){
        movementMap[x]=0;
    }
    pf->initMatrix(Vector2i(50, 50), movementMap);
    if(mode==0)pfBeginNode=pf->generatePathfind(Point2i(5, 4), Point2i(8, 20), 1);
    if(mode==1)psBeginNode=pf->generatePathfind(Point2i(7, 20), Point2i(7, 35), 1);
   //
   
}
void BeginMap::movement(){
    Core::Collision::BoundingBox b;
    
    b.size.x=this->p->getSprite()->getTileSize().x;
    b.size.y=ceil(this->p->getSprite()->getTileSize().y/2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::LShift, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(11, Core::InputControl::State::Held)){
        this->p->setPixelsPerCall(200);
        this->p->setChangeOnCall(10);
    }
    else{
        this->p->setChangeOnCall(15);
        this->p->setPixelsPerCall(150);
    }
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Right, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(5, Core::InputControl::State::Held)){
        //Check if the player can move
        //I need to get the float position from the player and add the movement to check if it is allowed
        b.position.x=this->p->getPosition().x+this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::RIGHT, true);
            this->p->setSpriteColumn(1);
            return;
        }
        
        
        //Move Player
        else if(this->p->getPosition().x < Game::window->sf::Window::getSize().x - Game::window->getSize().x*.2f){
            this->p->updateByKeyboard(Adventure::Character::Directions::RIGHT, Game::getDeltaTimef());
        }
        //Move Camera
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(-this->p->getPixelsPerCall()*Game::getDeltaTimef(), 0);
            this->p->updateDirection(Adventure::Character::Directions::RIGHT, true);
            this->p->call();
        }
    }
    
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Left, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(7, Core::InputControl::State::Held)){
        b.position.x=this->p->getPosition().x-this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.x < 0){
            this->p->updateDirection(Adventure::Character::Directions::LEFT, true);
            this->p->setSpriteColumn(1);
            return;
        }
        
        else if(this->p->getPosition().x >  Game::window->getSize().x*.2f || -this->mapManager.getMovement().x < 0)
            this->p->updateByKeyboard(Adventure::Character::Directions::LEFT, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(this->p->getPixelsPerCall()*Game::getDeltaTimef(), 0);
            this->p->updateDirection(Adventure::Character::Directions::LEFT, true);
            this->p->call();
        }
        
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Up, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y-this->p->getPixelsPerCall()*Game::getDeltaTimef()+b.size.y;
        
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.y < 0){
            this->p->updateDirection(Adventure::Character::Directions::UP, true);
            this->p->setSpriteColumn(1);
            return;
        }
        else if(this->p->getPosition().y >  Game::window->getSize().y*.2f || -this->mapManager.getMovement().y < 0)
            this->p->updateByKeyboard(Adventure::Character::Directions::UP, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(0, this->p->getPixelsPerCall()*Game::getDeltaTimef());
            this->p->updateDirection(Adventure::Character::Directions::UP, true);
            this->p->call();
        }
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Down, Core::InputControl::State::Held) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y+(this->p->getPixelsPerCall()*Game::getDeltaTimef())+b.size.y;
        
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::DOWN, true);
            this->p->setSpriteColumn(1);
            return;
        }
        else if(this->p->getPosition().y + b.size.y*2 <  Game::window->sf::Window::getSize().y - Game::window->getSize().y*.2f)
            this->p->updateByKeyboard(Adventure::Character::Directions::DOWN, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(0, -this->p->getPixelsPerCall()*Game::getDeltaTimef());
            this->p->updateDirection(Adventure::Character::Directions::DOWN, true);
            this->p->call();
        }
    }
}
void BeginMap::process(){
    Game::setDeltaTime();
    
    //bloqueia o movimento enquanto a animação ocorrer
    if(_p->getAutoMovement() && mode==0)
        return;
    // Seleciona uma opção do dialogo
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Up, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Released))
        d->prevOption();
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Down, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Released))
        d->nextOption();
    if(d->getRenderingQuestion()==true && (Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Return, Core::InputControl::State::Released )  || Core::InputControl::getJoystickButtonStatus(14, Core::InputControl::State::Released))){
        d->selectOption();
        renderText=false;
    }
    // Aceita uma opção do dialogo
    if((
       Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Return, Core::InputControl::State::Released)
        ||
        Core::InputControl::getJoystickButtonStatus(14, Core::InputControl::State::Released)
        ) && !d->getRenderingQuestion()){
        if(d->haveQuestion()){
            d->setRenderingQuestion(true);
        }
        else if(renderText){
            if(d->nextSpeech()==false)
                renderText=false;
        }
    }
    // Gera novo caminho, apos responder a pergunta
    if(!_p->getAutoMovement() && mode==1 && stopScript==false){
        generatePathForPlayer(1);
        _p->moveWithNodes(psBeginNode, mapManager.getMovementPointer(), Vector2i(60, 60), Vector2i(15, 15), 30);
        stopScript=true;
    }
    // bloqueio para a ultima animação
    if(!_p->getAutoMovement() && mode==1 && stopScript==false)
        return;
    // fim do script
    
    // desbloqueia o movimento
    if(!_p->getAutoMovement() && stopScript==true && !d->getRenderingQuestion()){
        movement();
        mapManager.process(p->getPosition().x, p->getPosition().y, 0, 0);
    }
}
void BeginMap::render(){
    mapManager.render(0, 0, Game::window->getSize().x, Game::window->getSize().y);
    p->render();
    MyGame::bs->render();
    MyGame::sl->render();
    if(!(mode==1 && !_p->getAutoMovement()))
        _p->render((Vector2i)mapManager.getMovement());
    if(
       (renderText && !_p->getAutoMovement())
       ||
       (mode==1 && _p->getAutoMovement())){
        d->renderSpeech();
        if(d->getRenderingQuestion())
            d->renderQuestion();
    }
}