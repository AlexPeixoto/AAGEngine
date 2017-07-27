//
//  Prototype.h
//  AAGEngine
//
//  Created by Alex Peixoto on 2/12/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Prototype__
#define __Action_Adventure_Game_Engine__Prototype__

#include "Point.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <thread>
#include "Sprite.h"
#include "Collision.h"
#include "Node.h"

namespace {
	const char MOVEMENTSHEET = 0;
	const char IDLESHEET = 1;
}

using sf::Point2f;
using sf::Point2i;
using Adventure::Sprite;
using Core::Node;
namespace Adventure{
    
            //! Classe que define um protótipo para personagens, NPC's e inimigos.
            class Character{
                
            public:
                //! Direções mapeadas para o qual o personagem pode estar "olhando".
                typedef enum class Directions{
                    NONE = 0, /*!< O personagem não esta "olhando" para nenhuma direção. */
                    DOWN = 1, /*!< O personagem esta "olhando" para baixo. */
                    UP = 2, /*!< O personagem esta "olhando" para cima. */
                    LEFT = 3, /*!< O personagem esta "olhando" para esquerda. */
                    RIGHT = 4 /*!< O personagem esta "olhando" para direita.. */
                } Directions;

                
            private:
                //! Define se existe um Sprite-Sheet de espera.
                /*! Define se o Sprite-Sheet de espera esta carregado.
                    Normalmente utilizado para momentos quando nenhum evento ocorre.
                 */
                bool idle;
                //! Define se existe um Sprite-Sheet de movimento.
                bool movement;
                //! Lista de Sprite-Sheets carregados.
                std::vector<Sprite*> *spriteList;
                //! Posição do personagem no mapa.
                Point2f position;
                //! Direção para a qual o personagem está "olhando".
                Directions facing;
                
                //How many calls the character is on the same frame
                //! Quantas vezes o método call foi chamado.
                int callsOnFrame;
                //! Após quantas chamadas do método call irá ocorrer uma troca de frames.
                int changeOnCall;
                //! Ultima direção para o qual o personagem estava "olhando".
                Directions lastDirection;
                //! Define se esta ocorrendo um movimento automatico do personagem;
                bool autoMovement;
            protected:
                //! Iterator que representa propriedade associada a chave.
				std::map<std::string, std::string>::const_iterator findProperty(const std::string& key);
                //! Mapa de propriedades do personagem.
				std::map<std::string, std::string>* properties;
                //! Returns the iterator that represents the item id and the quantity of that item
				std::map<int, int>::const_iterator findItemQuantity(int id);
                //! Map that associates the items on the character and its quantoty.
				std::map<int, int>* items;
                //! Which sprite is being rendered.
                int index;
                //! How many pixels are being added on the sprite position of each call's method (call).
                int pixelsPerCall;
                
                //! Retorna se os dois pontos são adjacentes
                virtual bool isAdjacent(const Point2i& p1, const Point2i& p2);
                
                //! Retorna a direção com base no movimento
                virtual Directions getDirectionFromMovement(const Vector2f& movement);
            public:
                //! Inicializa um personagem.
                /*! Inicializa um personagem com seu Sprite-Sheet que representa uma ação de espera.
                 \param idleSheet Sprite-Sheet que representa uma ação de espera.
                 \param tileWidth Largura do tile.
                 \param tileHeight Altura do tile.
                 */
                Character(const std::string& idleSheet, int tileWidth, int tileHeight);
                //! Inicializa um personagem.
                /*! Inicializa um personagem com seu Sprite-Sheet que representa uma ação de espera.
                 \param idleSheet Sprite-Sheet que representa uma ação de espera.
                 \param tileSize Alture e Largura do tile.
                 */
                Character(const std::string& idleSheet, Vector2i tileSize);
                //! Remove a lista de propriedades e sprites do personage,
                ~Character();
        
                //! Carrega Sprite-Sheet de movimento.
                /*! Carrega o Sprite-Sheet de movimento que será utilizado ao se mover o personagem. <br />
                    Este método somente pode ser chamado uma vez.
                 \param path Caminho do arquivo que contem o Sprite-Sheet de movimento.
                 \param tileWidth Largura do tile.
                 \param tileHeight Altura do tile.
                 \return Retorna se foi possivel carregar o Sprite-Sheet.
                 */
                virtual bool loadMovementSheet(const std::string& path, int tileWidth, int tileHeight);
                //! Carrega Sprite-Sheet de movimento.
                /*! Carrega o Sprite-Sheet de movimento que será utilizado ao se mover o personagem. <br />
                 Este método somente pode ser chamado uma vez.
                 \param path Caminho do arquivo que contem o Sprite-Sheet de movimento.
                 \param tileSize Alture e Largura do tile.
                 \return Retorna se foi possivel carregar o Sprite-Sheet.
                 */
                virtual bool loadMovementSheet(const std::string& path, Vector2i tileSize);
                //! Retorna direção que o personagem esta "olhando".
                virtual Directions getFacing();
        
                /*
                 *Sprite Manipulation
                 */
                //! Define após quantas chamadas do método call irá ocorrer uma troca de frames.
                virtual void setChangeOnCall(int changeOnCall);
                //! Define se o movimento do sprite é em loop, ou seja, se o indice atual do sprite for correspondente ao ultimo indice possivel do sprite ao se solicitar o avanço do indice ele retornará para o indice definido como indice de retorno.
                virtual void setLoop(bool loop);
                //! Define para qual indice deve-se retornar ao atingir o fim do sprite.
                virtual void resetLoopTo(int reset);
                //! Define a escala da altura do sprite que será renderizado.
                virtual void setHeightScale(int height);
                //! Define a escala da largura do sprite que será renderizado.
                virtual void setWidthScale(int width);
                
                //! Define quantos pixels devem ser adicionado no movimento a cada chamada do método call.
                virtual void setPixelsPerCall(int pixelsPerCall);
                //! Retorna quantos pixels devem ser adicionado no movimento a cada chamada do método call.
                virtual int getPixelsPerCall();
                //! Define qual coluna do sprite deve ser renderizada.
                virtual void setSpriteColumn(int column);
                //! Define qual linha do sprite deve ser renderizada.
                virtual void setSpriteRow(int row);
                //! Incrementa o indice da coluna do Sprite por 1.
                /*!
                 Incrementa o indice da coluna do Sprite por 1, caso o indice se encontre no ultime indice do sprite ele volta para o Sprite inicial ou para o valor definido na váriavel loopTo.
                 */
                virtual void next();
                //! Decrementa o indice da coluna Sprite por 1.
                /*!
                 Decrementa o indice da coluna do Sprite por 1, caso o indice se encontre no ultime indice do sprite ele volta para o indice que representa o fim do Sprite.
                 */
                virtual void prev();
                //! Executa uma chamada, se o numero de chamadas for superior ao maximo a coluna do sprite do personagem é alterada.
                virtual void call();
                //! Define uma nova direção para a qual o personagem estará olhando.
                /*! Define uma nova direção para a qual o personagem estará olhando.
                 \param direction Direção que se deseja que o personagem esteja "olhando".
                 \param updateY Define se é necessario  atualizar os indices do Sprite para alterar a imagem quando a mesma for renderizada.
                 */
                virtual void updateDirection(Directions direction, bool updateY);
                
                //! Renderiza personagem.
                virtual void render();
                //! Renderiza personagem atualizando sua posição.
                virtual void render(const Vector2i& movement);
                //! Altera qual Sprite-Sheet deve ser renderizado.
                virtual void changeSprite(int index);
        
                //Manage sprite position
                //! Retorna a posição do personagem no mapa.
                virtual Point2f getPosition();
                //! Adiciona valores a posição atual, util para movimentação com teclado/joystick.
                virtual void addToPosition(const Vector2i& addPosition);
                //! Altera a posição do personagem/
                virtual void setPosition(const Point2f& newPosition);
                //! Movimenta personagem de acordo com grafo.
                /*! Movimenta personagem de acordo com o grafo. É importante que o grafo esteja iniciando no ponto que o personagem se encontra e que o nó pai seja adjacente, caso o mesmo não ocorra a animação é interrompida.
                 \param nodes Nós que representam o caminho pelo qual o personagem deve se mover.
                 \param cameraMovement Pointeiro que representa o movimento da camera sobre o mapa para se calcular a posição final do personagem enquanto ele se move.
                 \param addMovimentPerSecond Numero de pixels que o personagem deve se mover por segundo.
                 \param tileSize Tamanho do tile a ser considerado. Provavelmente o pathfind foi feito considerando cada tile de colisão como 1x1, porem o movimento do personagem é real em relação ao mapa.
                 \param frameRate Numero de frames por segundo para executar o calculo de movimento por segundo.
                 
                 */
                virtual void moveWithNodes(Node* nodes, Vector2f* cameraMovement, const Vector2i& addMovimentPerSecond, const Vector2i& tileSize, float frameRate);
        
                //Returns the new sprite
                //! Adiciona novo Sprite.
                /*! Adiciona novo sprite a lista de sprites.
                 \param path Caminho do sprite a ser adicionado.
                 \param tileWidth Largura do tile do sprite.
                 \param tileHeight Altura do tile do sprite.
                 \return Retorna indice do sprite ou -1 caso o sprite não tenha sido adicionado
                 */
                virtual int addSprite(const std::string& path, int tileWidth, int tileHeight);
                //! Adiciona novo Sprite.
                /*! Adiciona novo sprite a lista de sprites.
                 \param path Caminho do sprite a ser adicionado.
                 \param tileSize Altura e Largura do tile do sprite.
                 \return Retorna indice do sprite ou -1 caso o sprite não tenha sido adicionado
                 */
                virtual int addSprite(const std::string& path, Vector2i tileSize);
                //Just disables the sprite, i need to maintain the index if not i mess with it
                //! Remove Sprite-Sheet no indice informado populando o indice com nullptr.
                virtual void disableSprite(int index);
                //! Retorna o indice do Sprite-Sheet atual.
                virtual int getIndex();
                //! Retorna Sprite-Sheet atual.
                virtual Sprite* getSprite() const;
                
                //! Adiciona uma nova propriedade ao personagem.
                /*!
                 \throw std::runtime_exception.
                 */
                virtual void addProperty(const std::string& key, const std::string& value);
                //! Atualiza uma propriedade existente.
                /*!
                 \return Retorna se a propriedade foi atualizada. Caso a propriedade não exista é retornado false.
                 \throw std::runtime_error/
                 */
                virtual void updateProperty(const std::string& key, const std::string& value);
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
                
                //! Adiciona novo item no personage, com a quantidade especificada.
                /*!
                 \throw std::exception
                 */
                virtual void addItem(size_t id, int quantity);
                //! Atualiza um quantidade de um item existente.
                /*!
                 \return Retorna se o item foi atualizada. Caso o item não exista é retornado false.
                 */
                virtual bool updateItem(size_t id, int quantity);
                //! Retorna a quantidade de itens da id associada.
                /*! Retorna a quantidade de itens dentro do personagem com a id associada.
                 \throw std::exception
                 */
                virtual int getItemQuantity(size_t id) const;
                //! Remove o item.
                /*!
                 \return Retorna se o item foi removido com sucesso. Caso o item não exista é retornado (false).
                 */
                virtual bool removeItem(size_t id);
                
                //! retorna se esta ocorrendo uma animação automatica.
                virtual bool getAutoMovement() const;
                
            };
}

#endif /* defined(__Action_Adventure_Game_Engine__Prototype__) */
