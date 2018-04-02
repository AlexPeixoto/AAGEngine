//
//  LevelManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__LevelManager__
#define __Action_Adventure_Game_Engine__LevelManager__

#include <iostream>
#include <thread>
#include "Level.h"
#include "BackgroundMusic.h"
#include "Game.h"

namespace Adventure{
    //! Classe que gerência niveis e mudança de niveis.
    class LevelManager{
    protected:
        //! Nivel que esta sendo carregado no momento.
        static Level *level;
        //! Define se está ocorrendo uma troca de niveis.
        static bool loading;
    public:
        //! ID do warp que foi colidido.
        /*! Contem o id do warp com o qual ocorreu colisão.
         Variável utilizada para fazer troca de niveis.
         */
        static int changeTo;
        //! Carrega nivel passado por parâmetro.
        /*!
            Carrega nivel passado por parâmetro. <br />
            O nivel será carregado fora do método, o método somente irá receber o ponteiro e definir o Level da classe como o Level passado por parâmetro.
         \throw std::runtime_error.
         */
        static void loadLevel(Level* level);
        //! Executa troca de niveis.
        /*! Inicializa troca de niveis, inicializando um nivel do tipo passado por parâmetro.
            \param params Lista de parametros passados para o novo nivel.
         */
        template<typename T>
        static void changeLevel(std::map<std::string, std::string> params){
            if(loading)
                throw std::runtime_error("[LevelManager] There is already a changeLevel call running");
            if(level==nullptr)
                throw std::runtime_error("[LevelManager] There is not a level to change");
            std::thread th([=](){
                LevelManager::changeTo=-1;
                loading=true;
                //Wait for all render calls stops (if it takes more than 100 millisenconds the game should have slowdowns, the acceptable is 1/30 of a second, 33 Milliseconds).
                //Needs to be fixed, mutex maybe?
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                delete level;
                level=nullptr;
                level=new T(params);
                loading=false;
            });
            th.detach();

        }
        //! Check if another level is being loaded.
        static bool getIsLoading();
        
        //! Executa o metodo render.
        /*! Renderiza executando o método render do nivel. <br />
            Caso esteja ocorrendo uma troca de niveis é executado o renderLoading().
         */
        static void render();
        //! Método de render executado entre troca de níveis.
        static void renderLoading();
        //! Executa o metodo process.
        /*! Renderiza executando o método process do nivel. <br />
         Caso esteja ocorrendo uma troca de niveis é executado o processLoading().
         */
        static void process();
        //! Método de process executado entre troca de níveis.
        static void processLoading();
        
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__LevelManager__) */
