//
//  Object.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Object__
#define __Action_Adventure_Game_Engine__Object__

#include <iostream>


#include <iostream>
#include "Point.h"
#include "Sprite.h"
using sf::Point2i;

namespace Adventure{
    class ObjectManager;
    //! Classe que define objeto no mapa.
    /*!
     Objeto é um Sprite que contém propriedades e itens atribuidos a ele.
     */
    class Object{
        friend class ObjectManager;
    protected:
        //! Sprite que representa objeto no mapa.
        Sprite* objectSprite;
        //! Caminho da imagem do objeto.
        std::string path;
        //! Nome do objeto.
        std::string name;
        //! Id do objeto.
        int id;
        //! Tamanho do tile do objeto.
        Vector2i tileSize;
        //! Posição do objeto no mapa.
        Point2i position;
        //! Define se o item que o objeto pode retornar é randomico
        bool randomize;
        //! Indice do tile do objeto.
        Point2i tileIndex;
        
        //! Iterator que representa propriedade associada a chave.
        std::map<std::string, std::string>::const_iterator findProperty(const std::string& key) const;
        //! Mapa de propriedades do objeto.
        std::map<std::string, std::string>* properties;
        
        //! Retorna iterator que representa item com a id associada assim como sua quantidade no objeto.
        std::map<int, int>::const_iterator findItem(int id);
        //! Mapa que associa itens contidos no objeto com sua quantidade.
        std::map<int, int>* items;
    public:
        //! Construtor utilizado pelo ObjectManager.
        Object();
        //! Inicializa objeto.
        /*!
         \param id ID unica do objeto.
         \param path Caminho da imagem que representa o objeto.
         \param name Nome do objeto.
         \param tileWidth Largura do tile do objeto.
         \param tileHeight Altura do tile do objeto.
         \param randomize Se o item a ser retornado deve ser randomizado.
         \param load Se é necessario carregar a imagem no construtor. Caso seja definido como (false) a imagem será carregada na primeira chamada de render.
         */
        Object(int id, const std::string& path, const std::string& name, int tileWidth, int tileHeight, bool randomize, bool load=false);
        //! Inicializa objeto.
        /*!
         \param id ID unica do objeto.
         \param path Caminho da imagem que representa o objeto.
         \param name Nome do objeto.
         \param tileSize Largura e altura do tile do objeto.
         \param randomize Se o item a ser retornado deve ser randomizado.
         \param load Se é necessario carregar a imagem no construtor. Caso seja definido como (false) a imagem será carregada na primeira chamada de render.
         */
        Object(int id, const std::string& path, const std::string& name, Vector2i tileSize, bool randomize,  bool load=false);
        //! Remove Sprite do objeto e apaga sua lista de propriedades.
        ~Object();
        
        //! Define caminho da imagem do Sprite e se o mesmo deve ser carregado no momento que a imagem é definida.
        virtual void setPath(const std::string& path, bool load=false);
        //! Define posição do objeto no mapa.
        virtual void setPosition(int x, int y);
        //! Define posição do objeto no mapa.
        virtual void setPosition(Point2i position);
        //! Define tamanho do tile do objeto.
        virtual void setTileSize(int tileWidth, int tileHeight);
        //! Define tamanho do tile do objeto.
        virtual void setTileSize(Vector2i tileSize);
        //! Define nome do objeto.
        virtual void setName(const std::string& name);
        //! Define se o item a ser retornado do objeto é randomico.
        virtual void setRandomize(bool randomize);
        //! Define em qual linha do tile do objeto.
        /*! A linha será calculada por row * tileSize.y */
        virtual void setRow(int row);
        //! Define em qual coluna do tile do objeto.
        /*! A coluna será calculada por column * tileSize.x */
        virtual void setColumn(int column);
        //! Define a linha e a coluna do tile do objeto.
        /*! A linha será calculada por row * tileSize.y. <br />
            A coluna será calculada por column * tileSize.x.
        */
        virtual void setTileIndex(Point2i tileIndex);
        //! Retorna o caminho do Sprite do objeto.
        virtual std::string getPath() const;
        //! Retorna o nome do objeto.
        virtual std::string getName() const;
        //! Retorna a posição do objeto no mapa.
        virtual Point2i getPosition() const;
        //! Retorna o tamanho do tile do objeto.
        virtual Vector2i getTileSize() const;
        //! Retorna a id do objeto.
        virtual int getId() const;
        //! Retorna se o item que será retornado será randomico.
        virtual bool getRandomize() const;
        //! Retorna a linha do tile do objeto.
        virtual int getRow() const;
        //! Retorna a coluna do tile do objeto.
        virtual int getColumn() const;
        //! Retorna a linha e a coluna do tile do objeto.
        virtual Point2i getTileIndex() const;
        
        //! Atualiza a posição no sprite.
        virtual void updateTileIndex();
        //! Renderiza objeto no mapa.
        virtual void render();
        
        //! Retorna sprite que representa este objeto.
        virtual Sprite* getSprite() const;
        //! Carrega sprite.
        virtual bool loadSprite();
        
        //! Adiciona uma nova propriedade ao objeto.
        /*!
         \throw std::runtime_exception.
         */
        virtual void addProperty(const std::string& key, const std::string& value);
        //! Atualiza uma propriedade existente.
        /*!
         \return Retorna se a propriedade foi atualizada. Caso a propriedade não exista é retornado false.
         \throw std::runtime_error.
         */
        virtual bool updateProperty(const std::string& key, const std::string& value);
        //! Retorna propriedade associada a chave.
        /*!
         \return Retorna propriedade associada a chave.
         \throw std::runtime_exception
         */
        virtual std::string getProperty(const std::string& key) const;
        //! Remove propriedade.
        /*!
         \return Retorna se a chave foi removida com sucesso. Caso a chave não exista é retornado (false).
         */
        virtual bool removeProperty(const std::string& key);
        //! Adiciona novo item no objeto com a quantidade especificada.
        /*!
         \throw std::exception
         */
        virtual void addItem(int id, int quantity);
        //! Atualiza um quantidade de um item existente.
        /*!
         \return Retorna se o item foi atualizada. Caso o item não exista é retornado false.
         */
        virtual bool updateItem(int id, int quantity);
        //! Retorna a quantidade de itens da id associada.
        /*! Retorna a quantidade de itens dentro do objeto com a id associada.
         \throw std::exception
         */
        virtual int getItemQuantity(int id) const;
        //! Remove o item.
        /*!
         \return Retorna se o item foi removido com sucesso. Caso o item não exista é retornado (false).
         */
        virtual bool removeItem(int id);

    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Object__) */
