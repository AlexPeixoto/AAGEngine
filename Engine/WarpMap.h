//
//  WarpMap.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__WarpMap__
#define __Action_Adventure_Game_Engine__WarpMap__

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "Point.h"
#include "WarpManager.h"
#include "Collision.h"

using namespace std;
using sf::Point2i;
using sf::Vector2i;
using Core::Collision;

namespace Adventure{
    //! Define, dentro do mapa, locais onde existem warps.
    class WarpMap{
    public:
        //! Estrutura que define um warp point dentro do mapa.
        typedef struct WarpFake{
            int id; /*!< Id do Warp. */
            Point2i position;  /*!< Posição do Warp. */
            bool enabled; /*!< Define se o Warp esta habilitado */
        } WarpFake;
        
    protected:
        //! Lista de warps carregados.
        vector<WarpFake*>* warpList;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de warp dentro do mapa será o definido no relativePath + nome do arquivo.
        static string relativePath;
        //! Inicializa vetor de warps.
        WarpMap();
        //! Inicializa vetor de warps.
        /*! Inicializa mapa de objetos utilizando o arquivo informado contendo a seguinte estrutura:<br />
         1. Inteiro contendo a quantidade de objetos que será carregado.<br />
         2. Inteiro contendo a id do warp.<br />
         3. Inteiro contendo o eixo x da posição do objeto no mapa.<br />
         4. Inteiro contendo o eixo y da posição do objeto no mapa.<br />
         O objeto é definido por padrão como habilitado.
         */
        WarpMap(string path);
        //! Remove os objetos carregados no mapa.
        ~WarpMap();
        
        //! Adiciona novo objeto.
        /*!
         \param id Id do warp que se deseja adicionar.
         \param x Posição no eixo x do warp.
         \param y Posição no eixo x do objeto.
         \param enabled Define se o warp esta habilitado.
         */
        virtual void addWarp(int id, int x, int y, bool enabled);
        //! Adiciona novo objeto.
        /*!
         \param id Id do warp que se deseja adicionar.
         \param position Posição x e y do warp.
         \param enabled Define se o warp esta habilitado.
         */
        virtual void addWarp(int id, Point2i position, bool enabled);
        //! Remove warp do indice.
        virtual void removeWarp(int index);
        
        //! Retorna lista com todos os warps.
        virtual vector<WarpFake*>* getWarpList() const;
        //! Retorna BoundingBox do warp passado por parametro.
        Core::Collision::BoundingBox getBoundingBox(WarpFake* w);
        
        //! Verifica se o BoundingBox colidiu com algum warp.
        /*!
         \param b BoundingBox do elemento que se deseja verificar a colisão.
         \param movement Movimento que esta ocorrendo em relação ao BoundingBox.
         \param changeTo Ponteiro que contem o valor do local de destino. Quando o mesmo for alterrado pelo warpProcessCollision deve-se trocar de nivel.
         */
        virtual void warpProcessCollision(Core::Collision::BoundingBox b, Vector2f movement, int* changeTo);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__WarpMap__) */
