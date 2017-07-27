//
//  CollisionMap.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/8/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__CollisionMap__
#define __Action_Adventure_Game_Engine__CollisionMap__

#include <iostream>
#include <exception>
#include "Point.h"
#include "Character.h"
#include "Collision.h"
#include <cmath>

using sf::Vector2f;

namespace Adventure{
    //! Define, dentro do mapa, locais onde ocorre colisão.
    class CollisionMap{
    private:
        //! Estrutura que define o número de blocos colisiveis e o tamanho dos blocos.
        struct CollisionStructure{
            Vector2i tileBlock; /*!< Numero de blocos em cada eixo. */
            Vector2i tileSize; /*!< Tamanho dos blocos. */
        } *collisionStructure;;
        //! Mapa de colisão.
        int16_t *collisionData;
        
    public:
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de collision será o definido no relativePath + nome do arquivo.
        static string relativePath;
        
        
        //! Inicializa ponteiros de estrutura e dados como inválidos.
        CollisionMap();
        //! Inicializa mapa de colisão utilizando o arquivo informado.
        /*! Inicializa mapa de colisão utilizando o arquivo informado contendo a seguinte estrutura:<br />
            Inteiro contendo o numero de blocos no eixo x.<br />
            Inteiro contendo o numero de blocos no eixo y.<br />
            Inteiro contendo a largura do bloco.<br />
            Inteiro contendo a altura do bloco.<br />
            Vetor de inteiros de 16 bits do tamanho numero_de_blocos_eixo_x*numero_de_blocos_eixo_y.
         */
        CollisionMap(string path);
        
        ~CollisionMap();
        
        //Check collision using a bounding box
        //! Retorna se o BoundingBox colide com algum bloco.
        /*! Retorna se o BoundingBox colide com algum bloco. <br />
            A verificação retorna (true) se o valor for maior que -1.
         \param b BoundingBox do elemento que se deseja verificar a colisão.
         \param movement Movimento que esta ocorrendo em relação ao BoundingBox.
         \return Retorna se ocorreu uma colisão.
         */
        bool collided(Core::Collision::BoundingBox b, Vector2f movement);
        //check if the movement to this direction is allowed
        //! Retorna se ocorre uma colisão com o ponto especificado.
        /*! Retorna se ocorre uma colisão com o ponto especificado. <br />
            A verificação retorna (true) se o valor for maior que -1.
         \return Retorna se ocorreu uma colisão.
         */
        bool collided(Point2i location);
        //! Retorna o valor de um bloco dentro do mapa.
        int getValue(int x, int y);
        //! Retorna o valor de um bloco dentro do mapa.
        int getValue(Point2i position);
        
        //! Define o valor de um bloco dentro do mapa.
        void setValue(int x, int y, int value);
        //! Define o valor de um bloco dentro do mapa.
        void setValue(Point2i position, int value);
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__CollisionMap__) */
