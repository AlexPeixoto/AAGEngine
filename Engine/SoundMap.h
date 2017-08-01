//
//  SoundMap.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__SoundMap__
#define __Action_Adventure_Game_Engine__SoundMap__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm> 
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include "Point.h"
#include "SoundEffectManager.h"

using sf::Point2i;
using sf::Sound;
using sf::Vector2i;

namespace Adventure{
    //! Define, dentro do mapa, locais onde existem sons.
    class SoundMap{
    private:
        //! Estrutura que define a representação de um som dentro do mapa.
        typedef struct SoundMapStructure{
            int id; /*!< Id do som. */
            Point2i position; /*!< Posição do som. */
            Sound* sound; /*!< Som no mapa */
        } SoundMapStructure;
        
        //! Posição do ouvinte no mapa.
        Point2i position;
        
        //! Lista de sons carregados.
        std::vector<SoundMapStructure*>* sounds;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de sons dentro do mapa será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        //! Inicializa vetor de sons e inicia a posição como inválida.
        SoundMap();
        //! Inicializa vetor de sons.
        /*! Inicializa mapa de sons utilizando o arquivo informado contendo a seguinte estrutura:<br />
         1. Inteiro contendo a quantidade de sons que será carregado.<br />
         2. Inteiro contendo a id do som.<br />
         Caso a id do som seja invalida o mesmo é ignorado.
         */
        SoundMap(const std::string& path);
        //! Remove os sons carregados no mapa.
        ~SoundMap();
        
        //! Inicia todos os sons.
        virtual void playAll();
        //! Adiciona ponteiro do SoundMapStructure informado na lista de warps.
        /*!
         \return Retorna se o SoundMapStructure passado por parametro ja existe.
         */
        virtual bool addSound(SoundMapStructure* sms);
        //! Remove som com base na id.
        virtual void removeSound(int id);
        //! Remove som com base na posição.
        virtual void removeSound(Point2i position);
        
        //! Atualiza posição do ouvinte no mapa.
        virtual void updatePosition(Point2i position);
        
        //! Retorna som com base na posição.
        virtual SoundMapStructure* getSound(Point2i position);
        //! Retorna vetor de sons.
        virtual std::vector<SoundMapStructure*>* getSounds() const;
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__SoundMap__) */
