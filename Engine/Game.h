//
//  Game.h
//  AAGEngine
//
//  Created by Alex Peixoto on 1/20/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Game__
#define __Action_Adventure_Game_Engine__Game__
#ifdef _WIN32
#include <functional>
#endif
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include "InputControl.h"
#include <SFML/Graphics.hpp>

using sf::Vector2;
using sf::Vector2i;
using sf::View;

namespace Core{
    class Game{
    protected:
        //! Estrutura que retorna o tempo.
        static sf::Time deltaTime;
        //! Define o tempo entre frames
        sf::Clock deltaClock;
        //! Metodo que deve ser sobrecarregado para processamento de parametros
        virtual void getParams(int argc, char** argv);
    private:
        //! Tamanho da tela
        Vector2i screenSize;
        //! Tempo entre frames.
        static float _deltaTime;
        //! Define se foi passado por parametro um functor para o método process.
        bool initProcessFunc;
        //! Define se foi passado por parametro um functor para o metodo render.
        bool initRenderFunc;
        //! Functor para o método process.
        std::function<void()> processFunc;
        //! Functor para o método render.
        std::function<void()> renderFunc;
    
    public:
        //! Ponteiro para qual tela deve ser efetuada a chamada de render pela classe Text.
        static sf::RenderWindow *window;
        //! Atualiza eventos que ocorreram pelo mouse, joystick e teclado.
        static sf::Event event;
        //! Inicializa a estrutura padrão do Game.
        /*!
         A execução da inicialização ocorre na seguinte ordem.<br />
            1. Inicializa parametros de contexto.<br />
            2. Chama init passando argc e argv para o mesmo. <br />
               A janela deve ser inicializada no init. <br />
         Se o framerate for definido como -1 é utilizado o vsync.
         */
         
        Game(std::function<void(int, char**)> init, int argc, char** argv);
        //! Inicializa estrutura padrão do game e sua janela.
        /*!
            1. Inicializa parâmetros de contexto.<br />
            2. Inicializa janela.<br />
            3. Chama método getParams.<br />
         Se o framerate for definido como -1 é utilizado o vsync.
         */
        Game(int width, int height, int framerate, const std::string& title, int argc, char** argv);
        ~Game();
    
        //! Define functor processFunc.
        virtual void setProcess(std::function<void()> processFunc);
        //! Define functor renderFunc
        virtual void setRender(std::function<void()> renderFunc);
        //! Processamento de eventos no jogo.
        /*! Processamento de eventos no jogo.
            O mesmo deve ser sobrecarregado ou deve-se definir um functor com setProcess.
         */
        virtual void process();
        //! Render de objetos no jogo.
        /*! Render de objetos no jogo.
         O mesmo deve ser sobrecarregado ou deve-se definir um functor com setRender.
         */
        virtual void render();
        
        //! Desabilita stretch no evento de resize.
        virtual void resize(int width, int height);
    
        //! Inicializa execução do jogo.
        /*! O jogo é executado em um loop que ocorre enquanto a janela não for fechada.
            Caso o processFunc tenha sido definido o mesmo é utilizado no processamento.
            Caso o renderFunc tenha sido definido o mesmo é utilizado no render.
         */
        virtual void run();
        
        //! Atualiza tempo entre frames.
        static void setDeltaTime();
        //! Return the time between frames.
        static float getDeltaTimef();
    
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__Game__) */
