//
//  Player.h
//  AAGEngine
//
//  Created by Alex Peixoto on 2/12/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Player__
#define __Action_Adventure_Game_Engine__Player__

#include <stdlib.h>
#include <iostream>
#include <map>
#include "Character.h"
#include "Game.h"
using std::string;
namespace Adventure{
        //! Define jogador.
        class Player : public Character{
        protected:
            //! Se adiciona na posição atual o numero de pixels informado.
            virtual void walkTo(Vector2i movement);
        public:
			//! Construtor Padrão
			Player();
            //! Inicializa do jogador.
            /*! Inicializa do jogador com seu Sprite-Sheet que representa uma ação de espera.
             \param idleSheet Sprite-Sheet que representa uma ação de espera.
             \param tileWidth Largura do tile.
             \param tileHeight Altura do tile.
             */
            Player(string idleSheet, int tileWidth, int tileHeight);
            //! Inicializa do jogador.
            /*! Inicializa do jogador com seu Sprite-Sheet que representa uma ação de espera.
             \param idleSheet Sprite-Sheet que representa uma ação de espera.
             \param tileSize Alture e Largura do tile.
             */
            Player(string idleSheet, Vector2i tileSize);
            ~Player();
            
            //! Renderiza personagem.
            virtual void render();
            //! Atualiza dados do personagem.
            virtual void process();
        
            //! Atualiza posição do personagem de acordo com a entrada do teclado.
            /*!
             \param direction Direção para qual se deseja mover o personagem.
             \param deltaTime Valor de deltaTime para se corrigir o movimento em caso deo frameskip.
             */
            virtual void updateByKeyboard(Directions direction, float deltaTime);
        
        };
}
#endif /* defined(__Action_Adventure_Game_Engine__Player__) */
