//
//  Location.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Location__
#define __Action_Adventure_Game_Engine__Location__

#include <iostream>
#include "Point.h"

namespace Core{
    //! Implementa classe Point2<Template>
    /*! Classe utilizada para representar objeto em um ponto da tela assim como seu tamanho*/
    template<typename T> class Location{
    public:
        //! Posição do objeto.
        sf::Point2<T> position;
        //! Tamanho do objeto.
        sf::Vector2<T> size;
    public:
        //! Define valor da posição do objeto no eixo x.
        void setX(T x);
        //! Define valor da posição do objeto no eixo y.
        void setY(T y);
        //! Define posição do objeto no eixo x e y.
        /*! Recebe um Point2 do tipo expecificado no template da classe.
         \param position Define posição do objeto na tela.
         */
        void setPosition(sf::Point2<T> position){
            this->position=position;
        }
        //! Define valor da posição do objeto no eixo x e y.
        void setPosition(T x, T y){
            this->position=sf::Point2<T>(x, y);
        }
        //! Retorna valor da posição do objeto no eixo x.
        T getX();
        //! Retorna valor da posição do objeto no eixo y.
        T getY();
        //! Retorna posição do objeto.
        /*!
         \return Retorna Point2 do tipo expecificado no template contendo a posição do objeto na tela.
         */
        sf::Point2<T> getPosition();
        
        //! Define largura do objeto.
        void setWidth(T width);
        //! Define altura do objeto.
        void setHeight(T height);
        //! Define tamanho do objeto.
        /*! Recebe um Vector2 do tipo expecificado no template da classe.
         \param size Define tamanho do objeto na tela.
         */
        void setSize(sf::Vector2<T> size){
            this->size=size;
        }
        void setSize(T width, T height){
            this->size=sf::Vector2<T>(width, height);
        }
        //! Retorna valor da largura.
        T getWidth();
        //! Retorna valor da altura.
        T getHeight();
        //! Retorna tamanho do objeto.
        /*!
         \return Retorna Vector2 do tipo expecificado no template contendo o tamanho do objeto.
         */
        sf::Vector2<T> getSize();
    };
    
    template<typename T>
    void Location<T>::setX(T x){
        this->position.x=x;
    }
    template<typename T>
    void Location<T>::setY(T y){
        this->position.y=y;
    }
    
    template<typename T>
    T Location<T>::getX(){
        return position.x;
    }
    template<typename T>
    T Location<T>::getY(){
        return position.y;
    }
    template<typename T>
    sf::Point2<T> Location<T>::getPosition(){
        return position;
    }
    
    template<typename T>
    void Location<T>::setWidth(T width){
        this->size.x=width;
    }
    template<typename T>
    void Location<T>::setHeight(T height){
        this->size.y=height;
    }
    template<typename T>
    T Location<T>::getWidth(){
        return size.x;
    }
    template<typename T>
    T Location<T>::getHeight(){
        return size.y;
    }
    template<typename T>
    sf::Vector2<T> Location<T>::getSize(){
        return size;
    }
    
}

#endif /* defined(__Action_Adventure_Game_Engine__Location__) */
