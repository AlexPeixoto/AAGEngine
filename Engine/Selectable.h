//
//  Selectable.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Selectable__
#define __Action_Adventure_Game_Engine__Selectable__

#include <iostream>
#include <vector>
#include "Image.h"
#include "BackgroundShape.h"

using namespace Core;

namespace Adventure{
    
    class Selectable : Location<int>{
    private:
        std::vector<Core::Image*> items;
        
        //! Indice do item selecionado
        size_t selectedItemIndex;
        //! Define a quantidade maxima de itens.
        int numberOfItemsPerScreen;
        //! Define o espaçamento lateral, superior e inferior entre items e será utilizado para ajustar o selectedItem shape subtraindo de sua posição a metade do espaçamento.
        int spacing;
        //! Define o fundo do item selecionado.
        BackgroundShape* selectedItem;
        //! Define o tamanho para cada item.
        /*!
          Não faz o stretch de imagens, o espaço somente é reservado e as imagens renderizadas no ponto(0, 0) em relação ao espaço reservado para a imagem.
         */
        Vector2i itemSize;
        //! Função chamada quando um item é selecionado.
        std::function<void (int, Selectable*)> callback;
    public:
        Selectable() = delete;
        //! Inicializa o selectable.
        Selectable(int numberOfItemsPerScreen, int spacing, BackgroundShape* selectedItem, Vector2i itemSize, Point2i position, std::function<void (int, Selectable*)> callback);
        
        //! Renderiza itens.
        virtual void render();
        //! Seleciona o item atual e dispara o callback.
        virtual void selectOption();
        
        //! Avança para o proximo item.
        virtual void nextItem();
        //! Retorna para o item anterior.
        virtual void prevItem();
        
        //! Define o numero de itens que aparecerão por tela.
        /*! Define o numero de itens que aparecerão por tela.
         \param numberOfItensPerScreen Numero de itens que aparecão a cada tela.
         */
        virtual void setNumberOfItemsPerScreen(int numberOfItemsPerScreen);
        //! Define o espaçamento entre os itens.
        /*! Define o espaçamento entre os itens.
         \param spacing Espaçamento entre os itens.
         */
        virtual void setSpacing(int spacing);
        //! Define o shape que irá indicar o item selecionado.
        /*! Ponteiro contendo o novo shape que será renderizado sob o item selecionado.
        \param selectedItem Ponteiro para o shape.
         */
        virtual void setSelectedShape(BackgroundShape* selectedItem);
        //! Adiciona uma nova imagem.
        /*! Adiciona uma nova imagem que pode ser selecionada.
        \param path Caminho da nova imagem.
         */
        virtual void addItem(const std::string& path);
        
        //! Retorna o número de itens.
        virtual int getNumberOfItemsPerScreen() const;
        //! Retorna o espaçamento entre itens.
        virtual int getSpacing() const;
        //! Retorna uma imagem no indice especificado.
        /*! Retorna uma imagem no indice especificado.
        \param index Indice do item que se deseja retornar o ponteiro para a imagem.
         */
        virtual Core::Image* getItem(size_t index) const;
        //! Retorna o shape que irá indicar o item selecionado.
        virtual BackgroundShape* getSelectedItemBackground() const;
        
        //! Retorna lista de itens.
        virtual const std::vector<Core::Image*>& getItems() const;
        
        //! Remove o item.
        /*! Remove o item.
         \param index Indice do item que se deseja remover.
         \return Retorna se foi possivel remover o item.
         */
        virtual bool removeItem(size_t index);
        
        //! Seleciona o item com base no click do mouse.
        /*! Seleciona um item que esteja dentro da área que o mouse clicou.
         \param clickedPosition Posição do mouse.
         */
        virtual void selectByMouse(Point2i clickedPosition);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Selectable__) */
