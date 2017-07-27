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
        //! Text that will be rendered along the image
        std::string text;
        //! Text position.
        Point2i textPosition;
        //! Image position.
        Point2i imagePosition;
        //! Text color.
        Color textColor;
        //! Text scale.
        Vector2f textScale;
        //! Image scale.
        Vector2f imageScale;
        //! Object responsible to render the text on the screen.
        TextControl* textControl;
        
    public:
        InformationImage() = delete;
        InformationImage(TextControl* textControl, const std::string& path, const std::string& text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor);
        
        virtual void render();
        
        virtual void setImagePath(const std::string& path);
        virtual void setText(const std::string& text);
        virtual void setImagePosition(const Point2i& imagePosition);
        virtual void setTextPosition(const Point2i& textPosition);
        virtual void setImageScale(const Vector2f& imageScale);
        virtual void setTextScale(const Vector2f& textScale);
        virtual void setTextColor(const Color& textColor);
        
        virtual string getImagePath() const;
        virtual Core::Image* getImage() const;
        virtual std::string getText() const;
        virtual Point2i getImagePosition() const;
        virtual Point2i getTextPosition() const;
        virtual Color getTextColor() const;
        virtual Vector2f getTextScale() const;
        virtual Vector2f getImageScale() const;
        
        
    };
}

#endif
