//
//  BackgroundMusic.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/23/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__BackgroundMusic__
#define __Action_Adventure_Game_Engine__BackgroundMusic__

#include <iostream>
#include <thread>
#include <algorithm>
#include <SFML/Audio/Music.hpp>

using namespace sf;

namespace Adventure{
    class BackgroundMusic{
    private:
        //! Musica que esta tocando no momento.
        static Music *playing;
        //! Musica que se deseja fazer a intersecção com a musica que esta tocando.
        static Music *intersect;
        //! Define se esta ocorrendo uma intersecção no momento.
        static bool onIntersection;
        //! Para a intersecção.
        static bool breakIntersection;
    public:
        //! Define o tipo de intersecção entre os sons.
        enum IntersectMode{
            NONE, /*!< Nenhuma intersecção, ao fim da primeira musica a segunda inicia. */
            CROSS, /*!< A musica que esta tocando diminui o volume até 0% e a musica que esta iniciando aumenta o volume até o volume maximo da primeira musica.. */
            FADEPLAYING /*!< A musica que esta tocando diminui o volume até 0%. A musica que vai tocar inicia com 100% de volume. */
        };
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de musica será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        
        
        //! Remove todas as musicas da memoria.
        ~BackgroundMusic();
        //! Carrega musica que será tocada, não deve ser utilizado para fazer intersecção entre musicas.
        static void loadSong(const std::string& path);
        //! Inicia a musica.
        /*!
         \return Retorna se foi possivel iniciar a musica.
         \throw std::runtime_exception
         */
        static bool play();
        //! Retorna a musica para o inicio e toca ela.
        /*!
         \return Retorna se foi possivel reiniciar a musica.
         \throw std::runtime_exception
         */
        static bool restart();
        //! Retorna a tocar a musica do mesmo momento que ela foi pausada.
        /*!
         \return Retorna se foi possivel resumir a musica.
         \throw std::runtime_exception
         */
        static bool resume();
        //! Para a musica.
        /*!
         \return Retorna se foi possivel parar a musica.
         \throw std::runtime_exception
         */
        static bool stop();
        //! Resume a musica.
        /*!
         \return Retorna se foi possivel pausar a musica.
         \throw std::runtime_exception
         */
        static bool pause();
        //! Para a musica que esta tocando e remove o ponteiro da musica.
        /*!
         \return Retorna se foi possivel deletar a musica.
         \throw std::runtime_exception
         */
        static bool close();
        //! Define se a musica deve ficar em loop.
        static void setloop(bool loop);
        //! Retorna se a musica deve ficar em loop.
        static bool returnLoop();
        
        //! Define volume da musica.
        static void setVolume(float volume);
        //! Retorna o volume da musica.
        static float returnVolume();
        
        //! Retorna o tempo que a musica ja tocou em segundos.
        static long getPositionInSeconds();
        //! Retorna o tempo total da musica em segundos.
        static long getDurationInSeconds();
        
        //The moment the intersectWith is called the intersect will run until the music ends
        //! Inicia intersecção entre a musica que esta tocando.
        /*!
         Inicia uma intersecção que ira fazer a troca entre duas musicas. <br />
         Até o fim da intersecção todos os metodos, exceto doBreakIntersection, todos os metodos estarao bloqueados.
         \param path Aquivo de som que irá interseder com a musica que esta tocando.
         \param im Modo de intersecção.
         \param timeToEnd Tempo de duração da intersecção.
         \throw std::runtime_exception.
         */
        static void intersectWith(const std::string& path, IntersectMode im, long long timeToEnd);
        //! Interrompe intersecção que esta ocorrendo.
        /*! Interrompe intersecção que esta ocorrendo. <br />
            Deve ocorrer somente quando se deseja recarregar todas as estruturas, como em uma troca de nivel.
         */
        static void doBreakIntersection();
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__BackgroundMusic__) */
