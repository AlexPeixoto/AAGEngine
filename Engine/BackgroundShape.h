//
//  Shape.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Shape__
#define __Action_Adventure_Game_Engine__Shape__

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Point.h"
#include "Location.h"
#include <SFML/Graphics.hpp>


//This class is basically an reimplementation of the sf::Rectangle shape, it is intended to be used as a background for texts on the screen

using sf::RectangleShape;
using sf::Texture;
using sf::Color;
using sf::Uint8;
using sf::Vector2f;
using std::string;
namespace Core{
    //! Implementa uma área retangula para ser utilizada como área de fundo.
    class BackgroundShape : public Location<int>{
    private:
        //! Ponteiro para qual tela deve ser efetuada a chamada de render pela classe Text.
        static sf::RenderWindow* window;
        //! Shape utilizada para representar a área
        RectangleShape shape;
        //! Textura representando uma imagem de fundo
        Texture* texture;
        //! Define cor da borda e de fundo
        Color insideColor, outlineColor;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de textura será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        
        //! Inicializa estruturas internas.
        BackgroundShape();
        //! Remove estruturas
        /*! Remove estruturas e deleta o ponteiro de textura caso ele tenha sido definido.*/
        ~BackgroundShape();
        //! Renderiza Shape na area definida e com o tamanho delimitado.
        /*! Renderiza Shape na area definida e com o tamanho delimitado pelos métodos: <br />
            setPosition.<br />
            setSize.<br />
            O Shape que será renderizado irá utilizar a cor definida como cor de fundo caso não exista uma textura. <br />
            Caso exista uma textura, está será utilizada como fundo do Shape.
         */
        virtual void render();
        
        //! Define tamanho da borda do Shape.
        /*! Define tamanho da borda do Shape.
         \param size Define tamanho da borda em pixels nos quatro lados do Shape.
         */
        virtual void setBorderSize(int size);
        //! Retorna tamanho da borda do Shape.
        virtual int getBorderSize();
        
        //! Carrega textura.
        /*! Carrega textura utilizando o caminho definido.
         \param path Define camiho onde se encontra a textura que deve ser carregada.
         \throw std::runtime_error.
         */
        virtual void loadTexture(const std::string& path);
        //! Remove textura da memoria
        virtual void unloadTexture();
        
        //! Define cor interna.
        /*! Define cor interna utilizando parametros RGBA.
         \param r Define valor do canal de cor vermelho (0-255).
         \param g Define valor do canal de cor verde (0-255).
         \param b Define valor do canal de cor azul (0-255).
         \param a Define valor do canal de cor alfa (0-255).
         */
        virtual void setInsideColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        //! Define cor interna.
        /*! Define cor interna utilizando sf::Color.<br />
         \param c Cor contendo {r, g, b, a}.
         */
        virtual void setInsideColor(Color c);
        //! Retorna cor interna.
        virtual Color getInsideColor();
        
        //! Define cor da borda.
        /*! Define cor da borda utilizando parametros RGBA.
         \param r Define valor do canal de cor vermelho (0-255).
         \param g Define valor do canal de cor verde (0-255).
         \param b Define valor do canal de cor azul (0-255).
         \param a Define valor do canal de cor alfa (0-255).
         */
        virtual void setBorderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        //! Define cor da borda.
        /*! Define cor da borda utilizando sf::Color.<br />
         \param c Cor contendo {r, g, b, a}.
         */
        virtual void setBorderColor(Color c);
        //! Retorna cor da borda.
        virtual Color getBorderColor();
        //! Define a tela onde deve ocorrer o processo de render da imagem.
        void static setWindow(sf::RenderWindow *window);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Shape__) */
