//
//  Slidebar.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Slidebar__
#define __Action_Adventure_Game_Engine__Slidebar__

#include <iostream>
#include "Point.h"
#include "Image.h"
#include "Location.h"
using Core::Image;
using Core::Location;
using sf::Point2i;

namespace Adventure{
    class Slidebar : public Location<int>{
    private:
        //! Valor selecionado.
        int selectedValue;
        
        //! Valor minimo.
        int minValue;
        //! Valor maximo.
        int maxValue;
        //! O quanto deve crescer ao se avançar ou retroceder.
        int increaseValue;
        //! Valor por pixel.
        int valuePerPixel;
        
        //! Imagem da barra que pode sofrer stretch na largura.
        Core::Image* slideBarImage;
        //! Imagem do elemento que fica sobre a barra de slide.
        Core::Image* slideElementImage;
        
        //! Função de callback
        std::function<void (int value)> callback;
        
        //! Atualiza posição em pixels do seletor da barra de slide.
        void updateSlidebarPosition();
    public:
        Slidebar();
        //! Inicializa a barra de slide.
        /*!
         Pode executar um throw caso o valor minimo e maximo não sejam multiplos do valor definido pelo increasce value
         \throw runtime_error
         */
        Slidebar(const std::string& slideBarPath, const std::string& slideElementPath, int minValue, int maxValue, int increaseValue, int valuePerPixel, Point2i position, std::function<void (int value)> callback);
        
        //! Renderiza a barra com o elemento sobre ela.
        virtual void render();
        
        //! Avança para o proximo valor aumentando pelo valor definido na variavel increasceValue.
        virtual bool prevValue();
        //! Retrocede para o proximo valor diminuindo pelo valor definido na variavel increasceValue.
        virtual bool nextValue();
        //! Define o valor.
        virtual bool setValue(int selectedValue);
        //! Retorna o valor selecionado na slidebar.
        virtual int getValue();
        
        //! Define valores da barra.
        virtual bool setValues(int minValue, int maxValue, int increaseValue);
        
        //! Retorna o valor minimo da barra.
        virtual int getMinValue() const;
        //! Retorna o valor maximo da barra.
        virtual int getMaxValue() const;
        //! Retorna o quanto o valor pode diminuir e aumentar.
        virtual int getIncreseValue() const;
        
        //! Atualiza a imagem da barra de slide.
        virtual void setSlideBarImage(const std::string& path);
        //! Atualiza a imagem do elemento que fica sobre a barra de slide.
        virtual void setSlideElementImage(const std::string& path);
        
        //! Altera a largura da imagem fazendo stretch horizontal da imagem.
        virtual void setSlideBarWidth(int width);
        //! Retorna largura da imagem sem o stretch.
        virtual int getSlideBarWidth();
        //! Retorna largura da imagem sem o stretch.
        virtual float getStretchedSlideBarWidth();

    };
}
#endif /* defined(__Action_Adventure_Game_Engine__Slidebar__) */
