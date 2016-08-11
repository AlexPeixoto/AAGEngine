//
//  MyGame.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 2/10/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "MyGame.h"

bool MyGame::mainMenuMode=true;
int MyGame::lastLoaded=-1;
int MyGame::loaded=-1;
bool MyGame::oneCross=false;
BackgroundShape *MyGame::bs=nullptr;
ScreenLog *MyGame::sl=nullptr;


MyGame::MyGame(int argc, char* argv[]) : Game(640, 480, -1, "Engine Sandbox", argc, argv){
    // Força o carregamento de imagens, sons, arquivos de mapas e itens de forma relativa.
    setRelativePaths();
    MyGame::getParams(argc, argv);
    initMainMenu();
    initGameMenu();
    
    BackgroundMusic::loadSong("/Users/alexpeixoto/Downloads/AF/menu.ogg");
    BackgroundMusic::setVolume(20);
    BackgroundMusic::play();
    
    //Inicia screenlog
    sl=new ScreenLog("/Developer/times.ttf");;
    
    //Define a janela principal para render de imagem e texto
    Core::Image::setWindow(Game::window);
    Core::TextControl::setWindow(Game::window);
    
    // Define arquivos genericos de itens e sons.
    ItemManager::loadFromFile("/Users/alexpeixoto/Desktop/item.list");

    
    
    // Inicializa um screenLog estático.
    sl->setPosition(Point2i(Game::window->getSize().x-250, 0));
    sl->setSize(Vector2i(250, 100));
    sl->setSpacing(5);
    sl->setScale(.5);
    
    // Inicializa debug
    Debug::LogManager::addLevelDestiny(Debug::LogLevel::WARNING, Debug::Destiny::Console);
    LogManager::addLevelDestiny(Debug::LogLevel::MESSAGE, Debug::Destiny::Screen, sl);
    LogManager::addLevelDestiny(Debug::LogLevel::WARNING, Debug::Destiny::Console, sl);
    
    bs=new Core::BackgroundShape();
    
    bs->setBorderSize(2);
    bs->setBorderColor(10, 100, 10, 255);
    bs->setInsideColor(100, 100, 0, 180);
    bs->setSize(Vector2i(260, 110));
    bs->setPosition(Point2i(Game::window->getSize().x-262, 2));
    
    //!Escreve no TTY, Caso deseje utilizar esta função abra o terminal e digite tty. Coloque o valor retornado no lugar do /dev/ttys000
    //LogManager::addLevelDestiny(Debug::LogLevel::ERROR, Debug::Destiny::Device, "/dev/ttys000", true);
    //LogManager::log(Debug::LogLevel::ERROR, "Teste", "");
    //LogManager::log(Debug::LogLevel::ERROR, "Teste", "");
    //LogManager::removeLevelDestiny(Debug::LogLevel::ERROR, Debug::Destiny::Device);

    thread t([=](){
        map<string, string> params;
        while(1){
            params.clear();
            //Aqui é verificado de onde veio a solicitação de mudança de nivel.
            if(Adventure::LevelManager::changeTo==0 && (loaded==-1 || loaded==0))
                LevelManager::changeLevel<ClosedMap>(params);
            else if(Adventure::LevelManager::changeTo==1 && (loaded==-1 || loaded==0))
                LevelManager::changeLevel<TestMap>(params);
            else if(Adventure::LevelManager::changeTo==2 && (loaded==-1 || loaded==0))
                LevelManager::changeLevel<ObjectMapGame>(params);
            
            else if(Adventure::LevelManager::changeTo==0 && loaded==1){
                params.insert(make_pair("position", "outHouse"));
                LevelManager::changeLevel<BeginMap>(params);
            }
            else if(Adventure::LevelManager::changeTo==0 && loaded==2){
                params.insert(make_pair("position", "outTest"));
                LevelManager::changeLevel<BeginMap>(params);
            }
            else if(Adventure::LevelManager::changeTo==0 && loaded==3){
                params.insert(make_pair("position", "outObject"));
                LevelManager::changeLevel<BeginMap>(params);
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });
    t.detach();
}
void MyGame::setRelativePaths(){
    CollisionMap::relativePath=TileMap::relativePath=ItemMap::relativePath=SoundMap::relativePath=ObjectMap::relativePath=WarpMap::relativePath=ItemManager::relativePath=SoundEffectManager::relativePath=ObjectManager::relativePath=WarpManager::relativePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/maps";
    SoundEffectManager::relativeInstancePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/sounds";
    BackgroundMusic::relativePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/musics";
    Core::Image::relativePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/images";
    TextControl::relativePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/fonts";
    TextTable::relativePath="C:/Users/bios2_000/Documents/GitHub/OGLEngine/EngineVS/x64/Debug/texts";
}
void MyGame::initMainMenu(){
    BackgroundShape::setWindow(Game::window);
    // Create main menu.
    mainMenu = new Dialog("times.ttf");
    
    //define caixa de dialogo
    speechBox=new Core::BackgroundShape();
    //define caixa da pergunta
    questionBox=new Core::BackgroundShape();;
    //define opção selecionada
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
    
    mainMenu->setSpeechColor(255, 255, 255, 255);
    mainMenu->setDialogBoxSize(Vector2i(Game::window->getSize().x, 200));
    mainMenu->setDialogBoxPosition(Point2i(0, Game::window->getSize().y-202));
    mainMenu->setSpeechBoxShape(speechBox);
    
    mainMenu->setQuestionColor(255, 255, 255, 255);
    mainMenu->setQuestionBoxSize(Vector2i(150, 40));
    mainMenu->setQuestionBoxPosition(Point2i(Game::window->getSize().x/2-60, 200));
    mainMenu->setQuestionBoxShape(questionBox);
    
    
    mainMenu->setQuestionBoxByLargest(true);
    
    mainMenu->setOptionInnerBorder(5);
    mainMenu->setOptionShape(optionShape);
    mainMenu->setOptionColor(255, 255, 255, 255);
	
	
    mainMenu->addSpeech(0, "Choose an option", false);
	
    mainMenu->addQuestion(0, "", [](int speechId, int questionId, int optionId, Dialog* dialog) -> void {
        dialog->setRenderingQuestion(false);
        if(speechId==0 && questionId==0 && optionId==0){
            map<string, string> param;
            LevelManager::loadLevel(new BeginMap(param));
            MyGame::mainMenuMode=false;
        }
        else if(speechId==0 && questionId==0 && optionId==1)
            exit(0);
        
    });
    
    mainMenu->addOption(0, 0, "New Game");
    mainMenu->addOption(0, 1, "Close");
    mainMenu->addDialogHandle(0, 0);
}
//inicializa o menu do jogo
void MyGame::initGameMenu(){
    //carrega menu do jogo
    gameMenu=new Menu("/Developer/times.ttf");
    //adicion checkbox
    gameMenu->addCheckbox("Callback test", "/Users/alexpeixoto/Desktop/background.jpg", "/Users/alexpeixoto/Desktop/selection.jpg", Point2i(0, 0), Point2i(35, 0), Color(100, 100, 100), [](bool state, Checkbox* c) -> void {
        cout << "Callback Checkbox: " << (int)state << endl;
    });
    //adiciona slidebar de tamanho 175 incrementando de 5 em 5
    gameMenu->addSlidebar("/Users/alexpeixoto/Desktop/slidebar.png", "/Users/alexpeixoto/Desktop/slidebarelement.png", 0, 175, 5, 1, Point2i(0, 50), [](int value) -> void {
        cout << "Callback Slidebar: " << (int)value << endl;
    });
    
    
    // adiciona drop down list
    gameMenu->addDropdown(5, 10, 2, Point2i(0, 100), [](int value, Dropdown* d){
        cout << "Callback DropDown: " << value << endl;
    });
    
    //Define menu de opções, carregando shapes
    BackgroundShape *menuS, *optionS, *boxS;
    menuS= new BackgroundShape();
    optionS = new BackgroundShape();
    boxS = new BackgroundShape();
    
    menuS->setBorderSize(1);
    optionS->setBorderSize(1);
    boxS->setBorderSize(1);
    
    menuS->setBorderColor(10, 10, 10, 255);
    optionS->setBorderColor(10, 10, 10, 255);
    boxS->setBorderColor(20, 20, 20, 255);
    
    menuS->setInsideColor(150, 150, 150, 255);
    optionS->setInsideColor(255, 30, 30, 255);
    boxS->setInsideColor(200, 40, 255, 255);
    //atribui shapes aos menus
    gameMenu->getDropdowns().at(0)->setMenuShape(menuS);
    gameMenu->getDropdowns().at(0)->setOptionShape(optionS);
    gameMenu->getDropdowns().at(0)->setBoxShape(boxS);
    gameMenu->getDropdowns().at(0)->setMenuOptionColor(Color(255, 255, 255));
    gameMenu->getDropdowns().at(0)->setSelectedOptionColor(Color(255, 255, 255));
    //adiciona opções
    gameMenu->getDropdowns().at(0)->addOption("Opção 1");
    gameMenu->getDropdowns().at(0)->addOption("Opção 2");
    gameMenu->getDropdowns().at(0)->addOption("Opção 3");
    gameMenu->getDropdowns().at(0)->addOption("Opção 4");
    gameMenu->getDropdowns().at(0)->addOption("Opção 5");
    gameMenu->getDropdowns().at(0)->addOption("Opção 6");
    
    
    // adiciona grupo de imagens selecionaveis
    BackgroundShape *bss = new BackgroundShape;
    bss->setInsideColor(255, 255, 0, 255);
    gameMenu->addSelectable(3, 4, bss, Vector2i(30, 30), Point2i(0, 150), [](int index, Selectable* s) -> void {
        cout << "Callback Selectable: " << index << endl;
    });
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i1.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i2.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i3.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i4.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i5.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i6.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i7.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i8.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i9.png");
    gameMenu->getSelectables().at(0)->addItem("/Users/alexpeixoto/Desktop/i10.png");
    // Setted
    game=true;
    row=0;

}
void MyGame::getParams(int argc, char **argv){
}
void MyGame::render(){
    if(mainMenuMode){
        mainMenu->renderSpeech();
        mainMenu->renderQuestion();
        
    }
    else{
        if(game)
            LevelManager::render();
        else
            gameMenu->render();
    }


}
void MyGame::process(){
    //se estiver no menu principal
    if(mainMenuMode){
        if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::C, Core::InputControl::State::Released) && !mainMenu->getRenderingQuestion()){
            if(mainMenu->haveQuestion()){
                mainMenu->setRenderingQuestion(true);
            }
        }
        //muda opção e aceita
        if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Up, Core::InputControl::State::Released)  || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Released))
            mainMenu->prevOption();
        else if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Down, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Released))
            mainMenu->nextOption();
        else if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Return, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(14, Core::InputControl::State::Released))
            mainMenu->selectOption();
    }
    //se nao for o menu principal
    else{
        //se estiver no jogo processa o metodo process do Level Manager
        if(game)
            LevelManager::process();
        //se nao, processa o menu do jogo
        else if(gameMenu->getElements().size()>0){
            int index;
            bool isAnOpenMenu=false;
            // Check if i have an open dropdown
            if(gameMenu->getElements().at(row)->type == Menu::TYPES::DROPDOWN){
                index=gameMenu->getElements().at(row)->index;
                if(gameMenu->getDropdowns().at(index)!=nullptr)
                    isAnOpenMenu=gameMenu->getDropdowns().at(index)->getOpenMenu();
            }
            // Move through the itens on the menu
            if(!isAnOpenMenu && (InputControl::getKeyboardKeyStatus(Keyboard::Down, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Released)))
                if(row<gameMenu->getElements().size() -1)
                    row++;
            if(!isAnOpenMenu && (InputControl::getKeyboardKeyStatus(Keyboard::Up, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Released)))
                if(row>0)
                    row--;
            
            
            if(InputControl::getKeyboardKeyStatus(Keyboard::Return, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(14, Core::InputControl::State::Released)){
                //Change checkbox status
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::CHECKBOX){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getCheckboxes().at(index)!=nullptr){
                        bool status=gameMenu->getCheckboxes().at(index)->getStatus();
                        gameMenu->getCheckboxes().at(index)->changeStatus(!status);
                    }
                }
                // Open a menu if i am selection one
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::DROPDOWN){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getDropdowns().at(index)!=nullptr){
                        bool status=gameMenu->getDropdowns().at(index)->getOpenMenu();
                        if(status==true)
                            gameMenu->getDropdowns().at(index)->selectOption();
                        gameMenu->getDropdowns().at(index)->setOpenMenu(!status);
                    }
                }
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::SELECTABLE){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getSelectables().at(index)!=nullptr)
                        gameMenu->getSelectables().at(index)->selectOption();
                }
            }
            
            //Handles the slidebar
            if(InputControl::getKeyboardKeyStatus(Keyboard::Left, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(7, Core::InputControl::State::Released)){
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::SLIDEBAR){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getSlidebars().at(index)!=nullptr)
                        gameMenu->getSlidebars().at(index)->prevValue();
                }
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::SELECTABLE){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getSelectables().at(index)!=nullptr)
                        gameMenu->getSelectables().at(index)->prevItem();
                }
            }
            if(InputControl::getKeyboardKeyStatus(Keyboard::Right, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(5, Core::InputControl::State::Released)){
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::SLIDEBAR){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getSlidebars().at(index)!=nullptr)
                        gameMenu->getSlidebars().at(index)->nextValue();
                }
                if(gameMenu->getElements().at(row)->type == Menu::TYPES::SELECTABLE){
                    index=gameMenu->getElements().at(row)->index;
                    if(gameMenu->getSelectables().at(index)!=nullptr)
                        gameMenu->getSelectables().at(index)->nextItem();
                }
            }
            
            
            // Lets deal with the drop down menu
            // Move trough the option
            if(isAnOpenMenu){
                Dropdown* d;
                d=gameMenu->getDropdowns().at(index);
                if(InputControl::getKeyboardKeyStatus(Keyboard::Down, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(6, Core::InputControl::State::Released))
                    d->next();
                else if(InputControl::getKeyboardKeyStatus(Keyboard::Up, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(4, Core::InputControl::State::Released))
                    d->prev();
            }
            
            
        }
        if(InputControl::getKeyboardKeyStatus(Keyboard::Z, InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(12, Core::InputControl::State::Released))
            game=!game;
    }
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Escape, Core::InputControl::State::Released) || Core::InputControl::getJoystickButtonStatus(0, Core::InputControl::State::Released))
        exit(0);
    

}