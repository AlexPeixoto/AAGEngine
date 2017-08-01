//
//  Node.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Node__
#define __Action_Adventure_Game_Engine__Node__

#include <iostream>
#include <vector>
#include "Point.h"

namespace {
	const uint32_t MAX_COST = 2147483640;
};

using sf::Point2i;

namespace Core{
    //! Define o nó para ser utilizado no <i> Pathfind </i>
    class Node{
    private:
        //! Ponteiro para o nó pai
        Node* parent;
        //! Lista de nós adjacentes
        std::vector<Node*> childNode;
        //! ID do nó, sendo essa a posição X e Y na matriz
        Point2i id;
        //! Custo para se mover deste nó até o destino
        int fCost;
        //! Custo para se mover até este nó
        int gCost;
        //! Custo do movimento no nó
        int movementCost;
        //! Nivel de clearance do nó
        int clearance;
        
    public:
        //! Construtor onde a posição é associada a um ID.
        /*!
         Construtor que recebe a posição do nó dentro da matriz como dois parametros.
         \param x Posição x do nó na matriz.
         \param y Posição y do nó na matriz.
         */
        Node(int x, int y);
        //! Construtor onde a posição é associada a um ID.
        /*!
         Construtor que recebe a posição do nó dentro da matriz como dois parametros.
         \param id Posição x e y definida por um Point2i.
         */
        Node(Point2i id);
        //! Adiciona o nó child.
        /*!
         Adiciona o ponteiro do nó child no nó atual.
         \param child Nó a ser adicionado.
         \return Retorna se foi possivel adicionar o nó.
        */
        bool addNode(Node* child);
        //! Remove nó filho
        /*! Remove ponteiro do nó filho 
         \param child Nó a ser removido
         */
        bool removeNode(Node* child);
        
        //! Retorna a ID do nó
        Point2i getID() const;
        //! Define a ID do nó
        /*!
         \param x Ponto x do nó na matriz
         \param y Ponto y do nó na matriz
         */
        void setID(int x, int y);
        
        //! Define o custo de F
        void setFCost(int costF);
        //! Retorna o custo de F
        int getFCost() const;
        
        //! Define o custo de G
        void setGCost(int costG);
        //! Retorna o custo de G
        int getGCost() const;
        
        //! Define o custo de movimento do nó
        void setMovementCost(int movementCost);
        //! Retorna o custo de movimento do nó
        int getMovementCost() const;
        
        //! Define o nó pai
        void setParent(Node* parent);
        
        //! Retorna o nó pai
        Node* getParent() const;
        
        //! Retorna todos os filhos do nó
        const std::vector<Node*>& getNodes() const;
        
        //! Define o nivel de clearance do nó
        void setClearance(int clearance);
        //! Retorna o nivel de clearance do nó
        int getClearance() const;
        
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Node__) */
