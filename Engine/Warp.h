//
//  Warp.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Warp__
#define __Action_Adventure_Game_Engine__Warp__

#include <iostream>
#include "Point.h"
#include "Sprite.h"
using sf::Point2i;

namespace Adventure{
    class WarpManager;
    //! Classe que define cada warp no mapa.
    class Warp{
        //! Permite que o WarpManager tenha acesso direto aos objetos.
        friend class WarpManager;
    protected:
        //! Define o caminho do arquivo que deve ser carregado ao se colidir com o warp.
        string path;
        //! Define o nome do warp.
        string name;
        //! Define a id do warp.
        int id;
        //! Define o tamanho do warp.
        Vector2i size;
        //! Define o ponto de destino que se deve colocar o personagem ao se carregar o mapa.
        Point2i destiny;
        
    public:
        //! Construtor utilizado pelo WarpManager.
        Warp();
        //! Inicializa warp
        /*
         \param id ID unica do warp.
         \param path Caminho onde se encontra arquivo que deve ser carregado ao se colidir com um warp.
         \param name Nome do warp.
         \param width Largura do warp.
         \param height Altura do warp.
         \param destinyX Posição x onde o personagem deve aparecer no mapa carregado.
         \param destinyy Posição y onde o personagem deve aparecer no mapa carregado.
         */
        Warp(int id, string path, string name, int width, int height, int destinyX, int destinyY);
        //! Inicializa warp
        /*
         \param id ID unica do warp.
         \param path Caminho onde se encontra arquivo que deve ser carregado ao se colidir com um warp.
         \param name Nome do warp.
         \param size Altura e largura do warp.
         \param destiny Posição x e y onde o personagem deve aparecer no mapa carregado.
         */
        Warp(int id, string path, string name, Vector2i size, Point2i destiny);
        
        //! Destrutor do Warp.
        ~Warp();
        
        //! Define caminho do arquivo que deve ser carregado ao se colidir com o warp.
        virtual void setPath(string path);
        //! Define tamanho do warp.
        virtual void setSize(int width, int height);
        //! Define tamanho do warp.
        virtual void setSize(Vector2i size);
        //! Define posição onde o personagem deve aparecer no mapa carregado.
        virtual void setDestiny(int x, int y);
        //! Define posição onde o personagem deve aparecer no mapa carregado.
        virtual void setDestiny(Point2i destiny);
        //! Define nome do warp.
        virtual void setName(string name);
        
        //! Retorna caminho do arquivo que deve ser carregado ao se colidir com o warp.
        virtual string getPath() const;
        //! Retorna nome do warp.
        virtual string getName() const;
        //! Retorna tamanho do warp.
        virtual Vector2i getSize();
        //! Retorna Posição onde o personagem deve aparecer no mapa carregado.
        virtual Point2i getDestiny();
        //! Retorna ID do warp.
        virtual int getId();
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Warp__) */
