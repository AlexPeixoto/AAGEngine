//
//  ObjectMap.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__ObjectMap__
#define __Action_Adventure_Game_Engine__ObjectMap__

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "Point.h"
#include "ObjectManager.h"
#include "Collision.h"

using sf::Point2i;
using sf::Vector2i;
using Core::Collision;

namespace Adventure{
    //! Define, dentro do mapa, locais onde existem objetos.
    class ObjectMap{
    public:
        //! Estrutura que define a representação de um objeto dentro do mapa.
        typedef struct ObjectFake{
            int id; /*!< Id do objeto. */
            Point2i position;  /*!< Posição do objeto. */
            Point2i spriteIndex; /*!< Indice do sprite do objeto. */
            bool collidable; /*!< Define se o objeto é colisivel. */
        } ObjectFake;
        
    protected:
        //! Lista de objetos carregados.
        std::vector<ObjectFake*>* objectList;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de objetos dentro do mapa será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        //! Inicializa vetor de objetos.
        ObjectMap();
        //! Inicializa vetor de objetos.
        /*! Inicializa mapa de objetos utilizando o arquivo informado contendo a seguinte estrutura:<br />
         1. Inteiro contendo a quantidade de objetos que será carregado.<br />
         2. Inteiro contendo a id do objeto.<br />
         3. Inteiro contendo o eixo x da posição do objeto no mapa.<br />
         4. Inteiro contendo o eixo y da posição do objeto no mapa.<br />
         O objeto é definido por padrão como colisivel.
         */
        ObjectMap(const std::string& path);
        //! Remove os objetos carregados no mapa.
        ~ObjectMap();
        
        //! Retorna se o BoundingBox colide com algum objeto.
        /*! Retorna se o BoundingBox colide com algum objeto. <br />
         \param b BoundingBox do elemento que se deseja verificar a colisão.
         \param movement Movimento que esta ocorrendo em relação ao BoundingBox.
         \return Retorna se ocorreu uma colisão.
         */
        bool collided(Core::Collision::BoundingBox b, Vector2f movement);
        //! Retorna se o BoundingBox colide com algum objeto.
        /*! Retorna se o BoundingBox colide com algum objeto. <br />
         \param b BoundingBox do elemento que se deseja verificar a colisão.
         \param movement Movimento que esta ocorrendo em relação ao BoundingBox.
         \return Indice do objeto no vetor com o qual ocorreu a colisão. Retorna -1 caso nenhuma colisão tenha ocorrido.
         */
        int collidedWith(Core::Collision::BoundingBox b, Vector2f movement);
        
        //! Adiciona novo objeto,
        /*!
         \param id Id do objeto que se deseja adicionar.
         \param position Posição do objeto.
         \param spriteIndex Indice do sprite.
         */
        void addObject(int id, Point2i position, Point2i spriteIndex);
        //! Adiciona novo objeto,
        /*!
         \param id Id do objeto que se deseja adicionar.
         \param x Posição no eixo x do objeto.
         \param y Posição no eixo x do objeto.
         \param spriteIndexY Indice do sprite no eixo x.
         \param spriteIndexX Indice do sprite no eixo y.
         */
        void addObject(int id, int x, int y, int spriteIndexX, int spriteIndexY);
        //! Remove objeto do indice.
        void removeObject(int index);
        
        //! Define indice do sprite do objeto especificado.
        void setSpriteIndex(int index, Point2i spriteIndex);
        //! Define indice do sprite do objeto especificado.
        void setSpriteIndex(int index, int spriteIndexX, int spriteIndexY);
        
        //! Define se o objeto no indice especificado é colisivel.
        void setCollidable(int index, bool collidable);
        
        //! Retorna o indice do Sprite.
        /*! Retorna o indice do Sprite.
         \param index Sprite que se deseja retornar o indice dentro do Sprite-sheet.
         \return Indice do sprite.
         \throw std::runtime_exception
         */
        virtual Point2i getSpriteIndex(int index) const;
        //! Retorna o indice do Sprite.
        /*! Retorna o indice do Sprite.
         \param index Sprite que se deseja retornar o indice dentro do Sprite-sheet.
         \return Indice do sprite no eixo x.
         \throw std::runtime_exception
         */
        virtual int getSpriteIndexX(int index) const;
        //! Retorna o indice do Sprite.
        /*! Retorna o indice do Sprite.
         \param index Sprite que se deseja retornar o indice dentro do Sprite-sheet.
         \return Indice do sprite no eixo y.
         \throw std::runtime_exception
         */
        virtual int getSpriteIndexY(int index) const;
        
        //! Retorna se o objeto do indice informado é colissivel.
        /*! Retorna se o objeto do indice informado é colissivel.
         \param index Objeto que se deseja retornar se é colissivel.
         \return Retorna se o objeto no indice informado é colissivel.
         \throw std::runtime_exception
         */
        bool getIsCollidable(int index) const;
        
        //! Renderiza objeto no mapa.
        /*! Renderiza objeto no mapa, na posição especificada com o tamanho delimitado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         */
        virtual void render(Point2i position, Vector2i size);
        //! Renderiza objeto no mapa.
        /*! Renderiza objeto no mapa, na posição especificada com o tamanho delimitado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         */
        virtual void render(int x, int y, int width, int height);
        
        //! Renderiza objeto no mapa ajustando o movimento.
        /*! Renderiza objeto no mapa ajustando o movimento.
         Porem o item no mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         \param movement Movimento que deve ser aplicado no mapa que será renderizado.
         */
        virtual void renderPerfect(Point2i position, Vector2i size, Vector2i movement);
        //! Renderiza objeto no mapa ajustando o movimento.
        /*! Renderiza objeto no mapa ajustando o movimento.
         Porem o item no mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         \param moveX Movimento que deve ser aplicado no eixo x do mapa que será renderizado.
         \param moveY Movimento que deve ser aplicado no eixo y do mapa que será renderizado.
         */
        virtual void renderPerfect(int x, int y, int width, int height, int moveX, int moveY);
        
        //! Retorna lista com todos os objetos.
        std::vector<ObjectFake*>* getObjectList() const;
        
        //! Retorna BoundingBox do objeto passado por parametro.
        Core::Collision::BoundingBox getBoundingBox(ObjectFake* o);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__ObjectMap__) */
