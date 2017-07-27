//
//  Map.h
//  AAGEngine
//
//  Created by Alex Peixoto on 1/20/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Map__
#define __Action_Adventure_Game_Engine__Map__

#include <iostream>
#include <vector>
#include "TileMap.h"
#include "Image.h"
#include "Collision.h"

using namespace std;

namespace Adventure{
    //! Define, dentro do mapa, multiplas camadas de tiles.
    class TileLayer {
    protected:
        //! Vetor contendo cada uma das camadas de tiles.
        vector<TileMap*>* tileList;
        
    public:
        //! Inicializa lista de TileMap.
        TileLayer();
        //! Inicializa lista de TileMap e carrega o primeiro tileManager
        TileLayer(string path);
        
        ~TileLayer();
        //! Carrega novo mapa na lista de TileMap.
        virtual void loadTileMap(string path);
        
        //! Renderiza mapa.
        /*! Renderiza mapa, correspondente ao indice, na posição especificada com o tamanho delimitado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         \param index Define qual indice do mapa será renderizado, caso informado -1 serão renderizado todos os mapas.
         */
        virtual void render(Point2i position, Vector2i size, int index=-1);
        //! Renderiza mapa.
        /*! Renderiza mapa, correspondente ao indice, na posição especificada com o tamanho delimitado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         \param index Define qual indice do mapa será renderizado, caso informado -1 serão renderizado todos os mapas.
         */
        virtual void render(int x, int y, int width, int height, int index=-1);
        
        //! Renderiza mapa ajustando o movimento.
        /*! Renderiza mapa, correspondente ao indice, na posição especificada com o tamanho delimitado.
            Porem o mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         \param movement Movimento que deve ser aplicado no mapa que será renderizado.
         \param index Define qual indice do mapa será renderizado, caso informado -1 serão renderizado todos os mapas.
         */
        virtual void renderPerfect(Point2i position, Vector2i size, Vector2i movement, int index=-1);
        //! Renderiza mapa ajustando o movimento.
        /*! Renderiza mapa, correspondente ao indice, na posição especificada com o tamanho delimitado.
         Porem o mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         \param moveX Movimento que deve ser aplicado no eixo x do mapa que será renderizado.
         \param moveY Movimento que deve ser aplicado no eixo y do mapa que será renderizado.
         \param index Define qual indice do mapa será renderizado, caso informado -1 serão renderizado todos os mapas.
         */
        virtual void renderPerfect(int x, int y, int width, int height, int moveX, int moveY, int index=-1);
        //! Retorna se o objeto informado está fora de algum dos TileMap.
        /*! Retorna se o objeto informado está fora de algum dos TileMap.
         \param x Posição do objeto no eixo x.
         \param y Posição do objeto no eixo y.
         \param width Largura do objeto.
         \param height Altura do objeto.
         \return Retorna se o objeto se encontra fora de algum TileMap.
         */
        virtual bool isEnd(int x, int y, int width, int height);
        //! Retorna se o objeto informado está fora de algum dos TileMap.
        /*! Retorna se o objeto informado está fora de algum dos TileMap.
         \param b BoundingBox do objeto.
         \return Retorna se o objeto se encontra fora de algum TileMap.
         */
        virtual bool isEnd(Core::Collision::BoundingBox b);
        
        //! Retorna o tile map no indice informado.
        virtual TileMap* getTileMap(int index);
    };
    
}

#endif /* defined(__Action_Adventure_Game_Engine__Map__) */
