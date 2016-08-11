//
//  InformationImage.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef OpenGL_Game_Engine_InformationImage_h
#define OpenGL_Game_Engine_InformationImage_h

#include <iostream>
#include "Image.h"
#include "Point.h"
#include "TextControl.h"

using namespace Core;

namespace Adventure{
    class InformationImage{
    private:
        //! Imagem que será mostrada
        Core::Image* image;
        //! Texto que será renderizado junto com a informação
        string text;
        //! Posição do texto.
        Point2i textPosition;
        //! Posição da imagem.
        Point2i imagePosition;
        //! Cor do texto.
        Color textColor;
        //! Escala do texto.
        Vector2f textScale;
        //! Escala da imagem
        Vector2f imageScale;
        //! Objeto que renderiza o texto na tela.
        TextControl* textControl;
        
    public:
        InformationImage() = delete;
        InformationImage(TextControl* textControl, string path, string text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor);
        
        virtual void render();
        
        virtual void setImagePath(string path);
        virtual void setText(string text);
        virtual void setImagePosition(Point2i imagePosition);
        virtual void setTextPosition(Point2i textPosition);
        virtual void setImageScale(Vector2f imageScale);
        virtual void setTextScale(Vector2f textScale);
        virtual void setTextColor(Color textColor);
        
        virtual string getImagePath() const;
        virtual Core::Image* getImage();
        virtual string getText();
        virtual Point2i getImagePosition();
        virtual Point2i getTextPosition();
        virtual Color getTextColor();
        virtual Vector2f getTextScale();
        virtual Vector2f getImageScale();
        
        
    };
}

#endif
