//
//  Item.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

//Here is stored the item definition from properties to tiles
#ifndef __Action_Adventure_Game_Engine__Item__
#define __Action_Adventure_Game_Engine__Item__

#include <iostream>
#include "Point.h"
#include "Sprite.h"
using sf::Point2i;

namespace Adventure{
    class ItemManager;
    //! Classe que define cada item existente.
    class Item{
        friend class ItemManager;
    protected:
        //! Sprite que representa o item.
        Sprite* itemSprite;
        //! Caminho da imagem do objeto.
        std::string path;
        //! Nome do item.
        std::string name;
        //! Id do item.
        int id;
        //! Tamanho do tile do item.
        Vector2i tileSize;
        //! Posição do item.
        Point2i position;
        //! Indice do tile do item.
        Point2i tileIndex;
        //! Iterator que representa propriedade associada a chave.
        std::map<std::string, std::string>::const_iterator findProperty(const std::string& key) const;
        //! Mapa de propriedades do item.
        std::map<std::string, std::string>* properties;
    public:
        //! Construtor utilizado pelo ItemManager.
        Item();
        //! Inicializa item.
        /*!
         \param id ID unica do item.
         \param path Caminho da imagem que representa o item.
         \param name Nome do item.
         \param tileWidth Largura do tile do item.
         \param tileHeight Altura do tile do item.
         \param load Se é necessario carregar a imagem no construtor. Caso seja definido como (false) a imagem será carregada na primeira chamada de render.
         */
        Item(int id, std::string&& path, std::string&& name, int tileWidth, int tileHeight, bool load=false);
        //! Inicializa item.
        /*!
         \param id ID unica do item.
         \param path Caminho da imagem que representa o item.
         \param name Nome do item.
         \param tileSize Largura e altura do tile do item.
         \param load Se é necessario carregar a imagem no construtor. Caso seja definido como (false) a imagem será carregada na primeira chamada de render.
         */
        Item(int id, std::string&& path, std::string&& name, Vector2i tileSize, bool load=false);
        //! Remove Sprite do item e apaga sua lista de propriedades.
        ~Item();
        
        //! Define caminho da imagem do Sprite e se o mesmo deve ser carregado no momento que a imagem é definida.
        virtual void setPath(string path, bool load=false);
        //! Define posição do item.
        virtual void setPosition(int x, int y);
        //! Define posição do item.
        virtual void setPosition(Point2i position);
        //! Define tamanho do tile do item.
        virtual void setTileSize(int Vector2i, int tileHeight);
        //! Define tamanho do tile do item.
        virtual void setTileSize(Vector2i tileSize);
        //! Define nome do item.
        virtual void setName(string name);
        //! Define em qual linha do tile do item.
        /*! A linha será calculada por row * tileSize.y */
        virtual void setRow(int row);
        //! Define em qual coluna do tile do item.
        /*! A coluna será calculada por column * tileSize.x */
        virtual void setColumn(int column);
        //! Define a linha e a coluna do tile do item.
        /*! A linha será calculada por row * tileSize.y. <br />
         A coluna será calculada por column * tileSize.x.
         */
        virtual void setTileIndex(Point2i tileIndex);
        
        //! Retorna o caminho do Sprite do item.
        virtual string getPath() const;
        //! Retorna o nome do item.
        virtual string getName() const;
        //! Retorna a posição do item.
        virtual Point2i getPosition();
        //! Retorna o tamanho do tile do item.
        virtual Vector2i getTileSize();
        //! Retorna a id do item.
        virtual int getId();
        //! Retorna a linha do tile do item.
        virtual int getRow();
        //! Retorna a coluna do tile do item.
        virtual int getColumn();
        //! Retorna a linha e a coluna do tile do item.
        virtual Point2i getTileIndex();
        
        //! Atualiza a posição no sprite.
        virtual void updateTileIndex();
        //! Renderiza objeto no mapa.
        virtual void render();
        
        //! Retorna sprite que representa este item.
        virtual Sprite* returnSprite() const;
        //! Carrega sprite.
        virtual bool loadSprite();
        
        //! Adiciona uma nova propriedade ao objeto.
        /*!
         \throw std::runtime_exception.
         */
        virtual void addProperty(string key, string value);
        //! Atualiza uma propriedade existente.
        /*!
         \return Retorna se a propriedade foi atualizada. Caso a propriedade não exista é retornado false.
         \throw std::runtime_error/
         */
        virtual bool updateProperty(string key, string value);
        //! Retorna propriedade associada a chave.
        /*!
         \return Retorna propriedade associada a chave.
         \throw std::runtime_exception
         */
        virtual string getProperty(string key);
        //! Remove propriedade.
        /*!
         \return Retorna se a chave foi removida com sucesso. Caso a chave não exista é retornado (false).
         */
        virtual bool removeProperty(string key);
        

    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Item__) */
