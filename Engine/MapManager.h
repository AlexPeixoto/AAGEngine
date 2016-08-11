//
//  MapManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 3/7/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//
/* Manages the map with all layers */
#ifndef __Action_Adventure_Game_Engine__MapManager__
#define __Action_Adventure_Game_Engine__MapManager__

#include <iostream>
#include "CollisionMap.h"
#include "TileLayer.h"
#include "ItemMap.h"
#include "SoundMap.h"
#include "ObjectMap.h"
#include "WarpMap.h"
#include "LevelManager.h"
using sf::Vector2f;
namespace Adventure{
    //! Classe que gerencia o mapa e todos os seus componentes.
    /*! Classe que implementa movimento de camera e utiliza deste movimento para renderizar/processar corretamente as classes de mapa.*/
    class MapManager{
    private:
        
        //! Define o gerenciamento de camadas de tiles.
        TileLayer *tl;
        //! Define o gerenciamento do mapa de colisão.
        CollisionMap *cm;
        //! Define o gerenciamento de itens no mapa.
        ItemMap* im;
        //! Define o posicionamento de sons no mapa.
        SoundMap* sm;
        //! Define o gerenciamento de objetos no mapa.
        ObjectMap* om;
        //! Define o gerenciamento de áreas de warp.
        WarpMap* wm;
        //! Define o movimento da camera.
        Vector2f movement;
    public:
        //! Inicializa estruturas utilizadas para gerenciar o movimento da camera.
        MapManager();
        //! Remove todos os objetos inicializados no MapManager
        ~MapManager();
        
        //! Carrega arquivo com definições de um mapa de tile.
        virtual bool loadTileLayer(string mapFile);
        //! Carrega arquivo com definições de um mapa de colisão.
        virtual bool loadCollisionMap(string collisionFile);
        //! Carrega arquivo com definições de um mapa de itens.
        virtual bool loadItemMap(string itemFile);
        //! Carrega arquivo com definições de um mapa de sons.
        virtual bool loadSoundMap(string soundFile);
        //! Carrega arquivo com definições de um mapa de objetos.
        virtual bool loadObjectMap(string objectFile);
        //! Carrega arquivo com definições de um mapa de warp.
        virtual bool loadWarpMap(string warpFile);
        
        //! Define TileLayer.
        virtual void setTileLayer(TileLayer* tl);
        //! Define TileLayer.
        virtual void setCollisionMap(CollisionMap* cm);
        //! Define TileLayer.
        virtual void setItemMap(ItemMap* im);
        //! Define TileLayer.
        virtual void setSoundMap(SoundMap* sm);
        //! Define TileLayer.
        virtual void setObjectMap(ObjectMap* om);
        //! Define TileLayer.
        virtual void setWarpMap(WarpMap* wm);
        //move the map, so the mapmanager calls the renderPerfect when render is called
        //! Adiciona valores ao movimento atual da camera.
        /*! Adiciona valores ao movimento atual da camera.
         \param x Define o movimento no eixo X a ser adicionado no movimento atual.
         \param y Define o movimento no eixo Y a ser adicionado no movimento atual.
         */
        virtual void move(float x, float y);
        
        //returns if it is the end of the map;
        //! Retorna se foi alcançado o fim do mapa de tiles.
        /*! Retorna se foi alcançado o fim do mapa de tiles.
         \param x Posição atual no eixo X do personagem no mapa.
         \param y Posição atual no eixo Y do personagem no mapa.
         \param width Largura do personagem no mapa.
         \param height Altura do personagem no mapa.
         \return Retorna se o personagem na posição especificada com o tamanho especificado está fora ou dentro do mapa.
         */
        virtual bool isEnd(int x, int y, int width, int height);
        
        //Check if each one of the maps are nullptr
        //! Renderiza mapa.
        /*! Renderiza mapa a partir da posição especificada com o tamanho especificado.
         O movimento do mapa é adicionado no posicionamento do mapa, porem isso não afeta o posicionamento na tela e sim o conteudo do mapa a ser renderizado.
         \param x Posição do eixo X de onde se deseja renderizar o mapa.
         \param y Posição do eixo Y de onde se deseja renderizar o mapa.
         \param height Altura do mapa que se deseja renderizar.
         \param width Largura do mapa que se deseja renderizar.
         */
        virtual void render(int x, int y, int height, int width);
        
        //! Processa sons no mapa.
        /*! Processa sons posicionais no mapa de acordo com a posição informada.
         O movimento do mapa é adicionado no posicionamento do objeto dentro mapa, porem isso não afeta o posicionamento na tela e sim como o som que se encontra proximo será tocado.
         \param x Posição do objeto que ouve os sons no eixo X.
         \param y Posição do objeto que ouve os sons no eixo Y.
         \param height Altura do objeto que ouve o som.
         \param width Largura do objeto que ouve o som.
         */
        virtual void process(int x, int y, int height, int width);
        
        //! Retorna se o BoundinBox passado por parametro colidiu com algum elemento da tela, a classe MapManager passa o movimento da camera para o CollisionMap.
        /*
         \param b BoundingBox contendo posição e tamanho do objeto que se deseja verificar colisão.
         \return Retorna se ocorreu colisão entre o BoundingBox passado por parametro e algum CollisionMap e ObjectMap, caso estejam instanciados.
         */
        virtual bool collided(Core::Collision::BoundingBox b);
        
        //! Retorna o movimento da câmera.
        virtual Vector2f getMovement();
        
        //! Retorna o movimento da câmera.
        virtual Vector2f* getMovementPointer();
        
        //! Retorna ponteiro para o gerenciador de camadas de tiles no mapa.
        virtual TileLayer* getTileLayer();
        //! Retorna ponteiro para o gerenciado de colisão no mapa.
        virtual CollisionMap* getCollisionMap();
        //! Retorna ponteiro para o gerenciador de itens no mapa.
        virtual ItemMap* getItemMap();
        //! Retorna ponteiro para o gerenciador de sons no mapa.
        virtual SoundMap* getSoundMap();
        //! Retorna o ponteiro para o gerenciador de objetos no mapa.
        virtual ObjectMap* getObjectMap();
        //! Retorna o ponteiro para o gerenciador de warp no mapa.
        virtual WarpMap* getWarptMap();
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__MapManager__) */
