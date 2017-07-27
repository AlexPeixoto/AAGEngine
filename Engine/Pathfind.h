//
//  Pathfind.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Pathfind__
#define __Action_Adventure_Game_Engine__Pathfind__
#ifdef _WIN32
#include <functional>
#endif
#include <iostream>
#include <cmath>
#include "Point.h"
#include "Node.h"

using sf::Point2i;
using sf::Vector2i;

namespace Core{
    //! Classe para gerar caminhos validos entre dois pontos
    /*!
     Classe que implementa Clearance A* Pathfind
     */
    class Pathfind{
    private:
        //! Define o mapa de movimento, sendo valores menores que 0 intransponiveis e valores maiores ou iguais a 0 transponiveis.
        int* moveMap;
        //! Define o numero de casas a direita e inferiores livres.
        int* clearanceMap;

        //! Ponteiro para o nó (0, 0)
        Node* firstNode;
        //! Ponteiro para o nó de inicio
        Node* beginNode;
        //! Tamanho da matriz
        Vector2i size;
        
        //!Função de heuristica.
        std::function<int (Point2i origin, Point2i destiny)> heuristicFunc;
        
        //bool diagonal (to return the correct heuristic method)
        bool diagonal;
        
        //! Retorna matriz de clearance da matriz passada como parametro
        /*!
         Retorna uma matriz, do mesmo tamanho da matriz passada por parametro onde cada indice indica o numero de casas inferiores e a direita livres.
         \param map Mapa passado por parametro
         \param size Tamanho do mapa
         \return Mapa do mesmo tamanho da matriz, porem com o clearance de cada casa.
         */
        int* returnWithClearance(int* map, Vector2i size);
        //! Retorna clearance de um nó
        /*!
         Retorna o clearance de um nó, utilizado pelo metodo <i> returnWithClearance </i>
         \param map Mapa passado por parametro
         \param origin Ponto de inicio da analize
         \param size Tamanho do mapa
        */
        int analyzeNode(int* map, Point2i origin, Vector2i size);
        
        //! Transforma matriz em um grafo
        /*!
         Transforma matriz passada por parametro e retorna o nó referente a posição (0, 0) da matriz
         \param clearanceMap Nivel de clearance para ser definido nos nós
         \param moveMap Mapa que define se é possivel se mover para o nó especificado
         \param size Tamanho do mapa
         \return Primeiro nó do grafo, representando o indice (0, 0)
         */
        Node* generateNodes(int* clearanceMap, int* moveMap, Vector2i size);
        //! Adiciona novo nó na lista aberta
        /*!
         Adiciona o nó origin dentro do node.
         \param clearanceMap Representação do mapa contendo o nivel de clearance de cada ponto do mapa.
         \param moveMap Representação dos nós sobre o qual pode se movimentar.
         \param size Tamanho do mapa.
         \param origin Posição do nó a ser adicionado no node. Estas sao as origens que levam a este no
         \param node Nó que se deseja adicionar o origin.
         \param ol Lista aberta de nós.
         \param cl Lista fechada de nós.
         \param iol Lista aberta de nós contendo a id como um inteiro.
         */
        void addNodeAndCheck(int* clearanceMap, int* moveMap, Vector2i size, Point2i origin, Node* node, std::vector<Node*>& ol, std::vector<Node*> cl, std::vector<int>& iol);
        //EOF Generate Nodes
        
        //! Verifica se a posição se encontra dentro do tamanho da matriz
        /*!
         Verifica se o nó é valido.
         \param size Tamanho da matriz.
         \param position Posição na matriz.
         \return Retorna se o ponto informado é valido.
         */
        bool isValid(Vector2i size, Point2i position);
        //! Retorna o melhor nó da lista
        /*!
         Retorna o nó dentro da lista que tem o menor custo F.
         \param openList Lista de nós abertos.
         \param remove Booleana para verificar se remove o nó ao retorna-lo.
         \return Retorna o melhor nó da lista.
         */
        Node* getBestOnList(std::vector<Node*>* openList, bool remove=true);
        //! Retorna um valor, com base na heuristica, para se mover da origem ao destino
        /*!
         Utilizando distancia de manhattan ou PERGUNTAR AO DIOGENES
         \param origin Ponto de origem
         \param destiny Ponto de destino
         \return Retorna custo aproximado para o movimento com base na heuristica.
         */
        int hMethod(Point2i origin, Point2i destiny);
    public:
        //! Inicializa estruturas internas do Pathfind
        Pathfind();
        //! Remove estruturas internas do Pathfind
        ~Pathfind();
        
        //! Retorna o primeiro nó com o caminho desde a origem até o destino com o clearance minimo informado
        /*!
         \param origin Ponto de origem do pathfind.
         \param destiny Ponto de destino do pathfind.
         \param clearance Valor minimo de clearance necessario pra poder se passar pelo nó.
         \return Retorna o nó de origem ou nullptr caso encontre nenhum caminho
         */
        Node* generatePathfind(Point2i origin, Point2i destiny, int clearance);
        //! Retorna o primeiro nó, posição (0, 0)
        /*!
         \return Retorna o nó referente a posição (0, 0)
         */
        Node* getFirstNode();
        //! Define o nó de origem
        /*! Define o nó de origem que representa a posição (x, y) da matrix. <br />
         Este nó será definido internamente e usado no método <i> generatePathfind </i>
         \param origin Posição da coordenada do nó desejado
         */
        void setOrigin(Point2i origin);
        //! Inicializa matriz de movimento, criando mapa de clearance e representação em grafo
        /*!
         \param size Tamanho da matriz a ser inicializada.
         \param moveMap Mapa de movimentação (vetor).
         \param diagonal Se deve-se considerar movimentos na diagonal.
         */
        void initMatrix(Vector2i size,  int* moveMap, bool diagonal=false);
        
        //! Inicializa matriz de movimento, criando mapa de clearance e representação em grafo
        /*!
         \param size Tamanho da matriz a ser inicializada.
         \param moveMap Mapa de movimentação (matriz).
         \param diagonal Se deve-se considerar movimentos na diagonal.
         */
        void initMatrix(Vector2i size,  int** moveMap, bool diagonal=false);

        //! Deleta nó principal e todos os seus filhos
        void deleteNodeContent();
        
        //! Define função de heuristica do pathfind.
        /*! Define função de heuristica do pathfind que será utilizada para calcular o custo no método generaePathfind.
         \param heuristicFunc Função de heuristica
         */
        void setHeuristicFunction(std::function<int (Point2i origin, Point2i destiny)> heuristicFunc);
        
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__Pathfind__) */
