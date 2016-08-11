//
//  Sprite.h
//  AAGEngine
//
//  Created by Alex Peixoto on 1/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Sprite__
#define __Action_Adventure_Game_Engine__Sprite__

#include <iostream>
#include "Image.h"
#include "Point.h"
#include <SFML/System/Vector2.hpp>

using sf::Point2i;
namespace Adventure{
    //! Classe que define um sprite
    /*!
     O Sprite é subdividido em areas do tamanho definido pelo tileSize.
     Cada uma destas areas é um tile.
     O Sprite renderiza a imagem contida dentro do tile especificado.
     */
    class Sprite : public Core::Image{
    protected:
        //! Define qual tile deve ser renderizado.
        Point2i index;
        //! Define o tamano do tile do sprite.
        Vector2i tileSize;
        //! Define se o percurso do tile será ciclico.
        /*! Define se ao atingir o ultimo tile e solicitar next() se o tile irá voltar para o indice especificado em loopTo */
        bool loopToBegin;
        //! Define o indice que se deve retornar caso o percurso dentro do tile seja ciclico.
        int loopTo;
    public:
        //! Inicializa Sprite.
        Sprite(string path, int tileWidth, int tileHeight);
        //! Inicializa Sprite.
        Sprite(string path, Vector2i tileSize);
        //! Remove Sprite carregado em memória.
        ~Sprite();
        
        /*Manage loop, like walk and the first image is standing, so i can remove this frame from loop*/
        //! Define se o percurso do tile será ciclico.
        void setLoop(bool loop);
        //! Define o indice que se deve retornar caso o percurso dentro do tile seja ciclico.
        void resetLoopTo(int index);
        
        //! Define o tamanho do tile.
        void setTileSize(float width, float height);
        //! Define o tamanho do tile.
        void setTileSize(Vector2i tileSize);
        
        //Move to the next and previous tile
        //! Incrementa o indice da coluna do Sprite por 1.
        /*! 
         Incrementa o indice da coluna do Sprite por 1, caso o indice se encontre no ultime indice do Sprite ele volta para o Sprite inicial ou para o valor definido na váriavel loopTo.
         */
        void next();
        //! Decrementa o indice da coluna Sprite por 1.
        /*!
         Decrementa o indice da coluna do Sprite por 1, caso o indice se encontre no ultime indice do Sprite ele volta para o indice que representa o fim do Sprite.
         */
        void prev();
        
        //! Incrementa o indice da linha do Sprite por 1.
        /*!
         Incrementa o indice da linha do Sprite por 1, caso o indice se encontre no ultime indice do Sprite ele volta para o Sprite inicial ou para o valor definido na váriavel loopTo.
         */
        void nextRow();
        //! Decrementa o indice da linha Sprite por 1.
        /*!
         Decrementa o indice da linha do Sprite por 1, caso o indice se encontre no ultime indice do Sprite ele volta para o indice que representa o fim do Sprite.
         */
        void prevRow();
        
        //! Define a linha do Sprite.
        void setRow(int row);
        //! Define a coluna do Sprite.
        void setColumn(int column);
        
        //! Renderiza o tile do Sprite na área definida pelo setPosition
        void render() override;
        //! Altera a imagem do Sprite.
        void changeSprite(string ImagePath, int tileWidth, int tileHeight);
        
        //! Retorna indice do tile do sprite.
        Point2i getSpriteIndex();
        //! Retorna tamanho do tile do Sprite.
        Vector2i getTileSize();
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Sprite__) */
