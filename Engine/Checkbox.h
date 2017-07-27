//
//  Checkbox.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Checkbox__
#define __Action_Adventure_Game_Engine__Checkbox__

#include <iostream>
#include "Location.h"
#include "Image.h"
#include "TextControl.h"

using Core::Image;
using Core::Location;

namespace Adventure{
    class Checkbox : public Location<int> {
    private:
        //! Define se o checkbox está selecionado ou não
        bool selected;
        
        //! Imagem de fundo, define também o tamanho que será retornado.
        Core::Image* background;
        //! Imagem que aparece dentro do checkbox quando selectionado.
        Core::Image* selection;
        
        //! Posição do texto.
        Point2i textPosition;
        
        //! Texto.
        string text;
        
        //! Objeto que renderiza o texto na tela.
        TextControl* textControl;
        
        //! Cor do texto
        Color color;
        
        //! Callback executado quando se alterar o status do checkbox.
        function<void (bool, Checkbox*)> callback;
        
    public:
        Checkbox() = delete;
        //! Construtor do checkbox.
        /*! Construtor do checkbox.
         \param text Texto que será exibido junto ao checkbox.
         \param backgroundPath Caminho da imagem que representa o checkbox na tela quando o checkbox não esta selecionado.
         \param selectionPath Caminho da imagem que representa o checkbox na tela quando o checkbox esta selecionado.
         \param position Posição do checkbox na tela.
         \param color Cor do texto.
         \param callback Função que será executada quando o checkbox for marcado ou desmarcado.
         */
        Checkbox(TextControl* textControl, string text, string backgroundPath, string selectionPath, Point2i textPosition, Color color, function<void (bool, Checkbox*)> callback);
        ~Checkbox();
        
        //! Define método de callback para quando o checkbox for selecionado
        virtual void setCheckedCallback(function<void (bool, Checkbox*)> callback);
        //! Altera status do checkbox
        virtual void changeStatus(bool selected);
        //! Renderiza o checkbox
        virtual void render();
        
        //! Carrega fundo do checkbox
        virtual bool loadBackground(string path);
        //! Carrega caixa que irá aparecer dentro do checkbox quando o mesmo for selecionado.
        virtual bool loadSelection(string path);
        //! Define texto a ser renderizado
        virtual void setText(string text);
        
        //! Define posição do checkbox na tela.
        virtual void setCheckboxPosition(Point2i position);
        //! Define posição do checkbox na tela.
        virtual void setCheckboxPosition(int x, int y);
        //! Define posição do texto na tela.
        virtual void setTextPosition(Point2i position);
        //! Define posição do texto na tela.
        virtual void setTextPosition(int x, int y);
        //! Define a cor do texto.
        virtual void setTextColor(Color color);
        
        //! Retorna a posição do checkbox.
        virtual Point2i getCheckboxPosition();
        //! Retorna a posição do texto.
        virtual Point2i getTextPosition();
        //! Retorna a cor do texto.
        virtual Color getTextColor();
        //! Retorna status.
        virtual bool getStatus();
        
        //! Retorna o tamanho do checkbox, sendo o mesmo o tamanho da imagem.
        virtual Vector2i getSize();
        
        //! Retorna texto.
        virtual string getText() const;
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Checkbox__) */
