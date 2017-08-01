//
//  ItemMap.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__ItemMap__
#define __Action_Adventure_Game_Engine__ItemMap__

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "Point.h"
#include "ItemManager.h"
#include "Collision.h"

using sf::Point2i;
using sf::Vector2i;
using Core::Collision;

namespace Adventure{
    //! Define, dentro do mapa, locais onde existem itens.
    class ItemMap{
    public:
        //! Estrutura que define a representação de um item dentro do mapa.
        typedef struct ItemFake{
            int id; /*!< Id do item. */
            Point2i position; /*!< Posição do item. */
            Point2i spriteIndex; /*!< Indice do sprite do item. */
        } ItemFake;
        
    protected:
        //! Lista de itens carregados no mapa.
        std::vector<ItemFake*>* itemList;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de itens dentro do mapa será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        //! Inicializa vetor de itens.
        ItemMap();
        //! Inicializa vetor de itens.
        /*! Inicializa mapa de itens utilizando o arquivo informado contendo a seguinte estrutura:<br />
            1. Inteiro contendo a quantidade de itens que será carregado.
            2. Inteiro contendo a id do item.
            3. Inteiro contendo o eixo x da posição do item no mapa.
            4. Inteiro contendo o eixo y da posição do item no mapa.
         */
        ItemMap(const std::string& path);
        //! Remove estruturas do item.
        ~ItemMap();
        //! Adiciona um item.
        /*! 
         \param id Id do item que se deseja adicionar.
         \param position Posição onde se deseja adicionar o item no mapa.
         */
        virtual void addItem(int id, Point2i position);
        //! Remove o item com o indice correspondente.
        virtual void removeItem(int index);
        
        //! Altera o indice do Sprite-Sheet do item.
        /*! Altera o indice do Sprite-Sheet do item.
         \param index Indice do item no vetor que se deseja alterar a posição dentro do Sprite-Sheet.
         \param spriteIndex Novo indice do Sprite-Sheet.
         \throw std::runtime_exception
         */
        virtual void setSpriteIndex(int index, Point2i spriteIndex);
        //! Altera o indice do Sprite-Sheet do item.
        /*! Altera o indice do Sprite-Sheet do item.
         \param index Indice do item no vetor que se deseja alterar a posição dentro do Sprite-Sheet.
         \param spriteIndexX Novo indice do Sprite-Sheet no eixo x.
         \param spriteIndexY Novo indice do Sprite-Sheet no eixo y.
         \throw std::runtime_exception
         */
        virtual void setSpriteIndex(int index, int spriteIndexX, int spriteIndexY);
        
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

        //! Renderiza item no mapa.
        /*! Renderiza item no mapa, na posição especificada com o tamanho delimitado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         */
        virtual void render(Point2i position, Vector2i size);
        //! Renderiza item no mapa.
        /*! Renderiza item no mapa, na posição especificada com o tamanho delimitado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         */
        virtual void render(int x, int y, int width, int height);
        
        //! Renderiza item no mapa ajustando o movimento.
        /*! Renderiza item no mapa ajustando o movimento.
         Porem o item no mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param position Posição onde o mapa será renderizado.
         \param size Tamanho do mapa.
         \param movement Movimento que deve ser aplicado no mapa que será renderizado.
         */
        virtual void renderPerfect(Point2i position, Vector2i size, Vector2i movement);
        //! Renderiza item no mapa ajustando o movimento.
        /*! Renderiza item no mapa ajustando o movimento.
         Porem o item no mapa que será renderizado é ajustado de acordo com o movimento informado.
         \param x Posição no eixo x onde o mapa será renderizado.
         \param y Posição no eixo y onde o mapa será renderizado.
         \param width Largura do mapa.
         \param height Altura do mapa.
         \param moveX Movimento que deve ser aplicado no eixo x do mapa que será renderizado.
         \param moveY Movimento que deve ser aplicado no eixo y do mapa que será renderizado.
         */
        virtual void renderPerfect(int x, int y, int width, int height, int moveX, int moveY);
        
        //! Retorna lista com todos os itens.
        virtual std::vector<ItemFake*>* getItemList() const;
        
        //! Retorna BoundingBox do item passado por parametro.
        virtual Core::Collision::BoundingBox getBoundingBox(ItemFake* i) const;
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__ItemMap__) */
