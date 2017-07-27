//
//  Image.h
//  OpenGL Window
//
//  Created by Alex Peixoto on 11/22/13.
//  Copyright (c) 2013 Alex Peixoto. All rights reserved.
//

#ifndef __OpenGL_Window__Image__
#define __OpenGL_Window__Image__
#include <iostream>
#include <sstream>
#include "LogManager.h"
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using sf::Vector2;
using sf::Vector2i;
using sf::Vector2f;
using sf::Point2i;
using sf::Point2f;
using Debug::LogLevel;
using Debug::LogManager;

namespace Core{
    class Image{
    private:
        //! Define textura da imagem
        sf::Texture* texture;
        //! Define sprite, que irá renderizar a textura.
        sf::Sprite* sprite;
        
    protected:
        //! Ponteiro para qual tela deve ser efetuada a chamada de render pela classe Text.
        static sf::RenderWindow *window;
        //! Tamanho da escala do sprite
        Vector2f frameSize;
        //! Define caminho da textura
        std::string path;
        //! Set position of the frame on the screen
        Point2i framePos;
        
        //! Image Rotation
        float rotation;
    
        //! Center of the image
        Point2i origin;
        
        //! Texture Size
        Vector2<unsigned> textureSize;
    
        //! Specifies if the image is being reloaded
        bool reloading;
 
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de imagem será o definido no relativePath + nome do arquivo.
        static string relativePath;
        //! Inicializa Imagem.
        /* Inicializa textura utilizando imagem no caminho especificado assim como sprite que irá carregar a textura. <br />
           Caso não seja possivel carregar a imagem é gerada uma excessão do tipo std::runtime_exception.
           \param path Caminha da imagem.
         */
        Image(string path);
        //! Remove estruturas da imagem.
        ~Image();
        //! Altera imagem chamando o construtor Image().
        virtual void changeImage(string path);
    
        //! Render the image on the specified position
        /*! Render the image ont he position specified by the methid <i>setPosition</i>*/
        virtual void render();
        
        //! Define internamente a fonte.
        /*! Define a nova fonte que será carregada, carregando a mesma.
         \param position Posição dentro da textura.
         \param size Tamanho da area a ser renderizada dentro da textura.
         */
        virtual void renderSub(Point2f position, Vector2f size);
        //! Define internamente a fonte.
        /*! Define a nova fonte que será carregada, carregando a mesma.
         \param x Posição x dentro da textura.
         \param y Posição y dentro da textura.
         \param width Largura da textura da area a ser renderizada dentro da textura.
         \param height Altura da textura da area a ser renderizada dentro da textura.
         */
        virtual void renderSub(float x, float y, float width, float height);

        //! Define escala da textura no eixo x.
        /*
         \param width Escala da textura no eixo x.
         */
        virtual void setWidthScale(float width);
        //! Define escala da textura no eixo y.
        /*!
         \param height Escala da textura no eixo y.
         */
        virtual void setHeightScale(float height);
        //! Define a escala da textura.
        /*!
         \param scale Escala da textura nos dois eixos.
         */
        virtual void setScale(Vector2f scale);
        //! Retorna escala da textura no eixo x.
        virtual float getWidthScale();
        //! Retorna escala da textura no eixo y.
        virtual float getHeightScale();
        //! Retorna um vetor contendo as duas escalas da imagem.
        /*! Retorna um vetor contendo as duas escalas da imagem.
         \return Vetor contendo as duas escalas da imagem.
         */
        virtual Vector2f getScale();
        
        //! Define a posição no eixo x onde deve-se renderizar a imagem.
        /*!
         \param x Posição em x onde a imagem deve ser renderizada na tela.
         */
        virtual void setX(int x);
        //! Define a posição no eixo y onde deve-se renderizar a imagem.
        /*!
         \param y Posição em y onde a imagem deve ser renderizada na tela.
         */
        virtual void setY(int y);
        //! Define a posição no eixo x e y de onde deve-se renderizar a imagem.
        /*!
         \param position Posição x e y da imagem na tela.
         */
        virtual void setPosition(Point2i position);
        //! Define angulo de rotação da imagem
        /*! Define o angulo de rotação da imagem entre 0 e 360˚
         \param rotation Define a rotação da imagem.
         */
        virtual void setRotation(float rotation);
        
        
        //! Define o ponto de origem da imagem.
        virtual void setOrigin(Point2i origin);
        
        //! Retorna posição da imagem no eixo x.
        virtual int getY();
        //! Retorna posição da imagem no eixo y.
        virtual int getX();
        //! Retorna estrutura contendo a posição da imagem no eixo x e y.
        virtual Point2i getPosition();
        
        //! Retorna largura da imagem.
        virtual int getWidth();
        //! Retorna altura da imagem.
        virtual int getHeight();
        //! Retorna estrutura contendo largura e altura da imagem.
        virtual Vector2<unsigned> getSize();
        
        //! Retorna o angulo de rotação da imagem.
        virtual float getRotation();
        
        //! Retorna a origem da imagem.
        virtual Point2i getOrigin();
    
        //! Retorna o caminho da imagem.
        virtual string getPath() const;
        //! Define a tela onde deve ocorrer o processo de render da imagem.
        void static setWindow(sf::RenderWindow *window);
        
        //! Retorna Sprite do SFML utilizado na classe Image.
        virtual sf::Sprite* getSfSprite();
        //! Retorna Textura do SFML utilizado na classe Image.
        virtual sf::Texture* getSfTexture();
    
    };
}
#endif /* defined(__OpenGL_Window__Image__) */
