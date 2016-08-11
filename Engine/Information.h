//
//  Information.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef OpenGL_Game_Engine_Information_h
#define OpenGL_Game_Engine_Information_h

#include <iostream>
#include "Point.h"
#include "TextControl.h"

using namespace std;
using namespace Core;

namespace Adventure{
    //! Define uma informação que será mostrada na tela.
    /*! Informações definidas aqui não poderão ter multiplas telas. */
    class Information{
    private:
        //! Posição da informação.
        Point2i position;
        //! Texto da informação.
        string text;
        //! Tamanho da informação na tela.
        Vector2f scale;
        //! Cor do texto
        Color color;
        //! Objeto que renderiza o texto na tela.
        TextControl* textControl;
    public:
        //! Remove construtor padrão.
        Information() = delete;
        //! Construtor da informação que deve aparecer na tela.
        /*! Construtor da informação que deve aparecer na tela.
         \param information Texto que será exibido na tela.
         \param scale Escala do texto que será exbibido na tela.
         \param position Posição do texto na tela.
         \param Cor do texto na tela.
         */
        Information(TextControl* textControl, string text, Vector2f scale, Point2i position, Color color);
        
        //! Renderiza o texto.
        virtual void render();
        
        //! Define cor do texto.
        virtual void setColor(Color color);
        //! Define tamanho do texto.
        virtual void setScale(Vector2f scale);
        //! Define o texto.
        virtual void setText(string text);
        //! Define posição do texto na tela.
        virtual void setPosition(Point2i position);
        
        //! Retorna cor do texto.
        virtual Color getColor();
        //! Retorna tamanho do texto.
        virtual Vector2f getScale();
        //! Retorna o texto.
        virtual string getText();
        //! Retorna posição do texto.
        virtual Point2i getPosition();
        
    };
}


#endif
