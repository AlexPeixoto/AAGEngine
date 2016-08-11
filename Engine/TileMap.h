//
//  TileManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 1/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__TileManager__
#define __Action_Adventure_Game_Engine__TileManager__

#ifdef _WIN32
#include <cstdint>
#endif
#include <iostream>
#include <cmath>
#include "Image.h"
#include "Point.h"

using sf::Point2i;
namespace Adventure{
        //! Define, dentro do mapa, locais onde existem tiles.
        class TileMap{
        protected:
            //! Estrutura que define o número de tiles e o tamanho de cada tile.
            struct TileStructure{
                Vector2i tileBlock; /*!< Numero de blocos em cada eixo. */
                Vector2i tileSize; /*!< Tamanho dos blocos. */
                char filename[255]; /*!< Nome do arquivo que contem os tiles. */
            } *tileHeader;
            
        private:
            //! Carrega imagem de tiles contida no header.
            void loadTiles();
            //! Carrega nivel com base no arquivo passado por parametro.
            void loadLevel(string path);
            
            //! Mapa de tiles.
            int16_t* tileData;
            //! Imagem 
            Core::Image* tileImage;
        public:
            //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de tiles será o definido no relativePath + nome do arquivo.
            static string relativePath;
            //! Inicializa ponteiros de estrutura e dados como inválidos.
            TileMap();
            //! Inicializa mapa de tiles utilizando o arquivo informado.
            /*! Inicializa mapa de tiles utilizando o arquivo informado contendo a seguinte estrutura:<br />
             Inteiro contendo o numero de blocos no eixo x.<br />
             Inteiro contendo o numero de blocos no eixo y.<br />
             Inteiro contendo a largura do bloco.<br />
             Inteiro contendo a altura do bloco.<br />
             Vetor de inteiros de 16 bits do tamanho numero_de_blocos_eixo_x*numero_de_blocos_eixo_y.
             */
            TileMap(string path);
            //! Apaga estruturas do tilemap.
            ~TileMap();
            
            //! Renderiza mapa.
            /*! Renderiza mapa, na posição especificada com o tamanho delimitado.
             \param position Posição onde o mapa será renderizado.
             \param size Tamanho do mapa.
             */
            virtual void render(Point2i position, Vector2i size);
            //! Renderiza mapa.
            /*! Renderiza mapa, na posição especificada com o tamanho delimitado.
             \param x Posição no eixo x onde o mapa será renderizado.
             \param y Posição no eixo y onde o mapa será renderizado.
             \param width Largura do mapa.
             \param height Altura do mapa.
             */
            virtual void render(int x, int y, int width, int height);
            
            //! Renderiza mapa ajustando o movimento.
            /*! Renderiza mapa ajustando o movimento.
             Porem o mapa que será renderizado é ajustado de acordo com o movimento informado.
             \param position Posição onde o mapa será renderizado.
             \param size Tamanho do mapa.
             \param movement Movimento que deve ser aplicado no mapa que será renderizado.
             */
            virtual void renderPerfect(Point2i position, Vector2i size, Vector2i movement);
            //! Renderiza mapa ajustando o movimento.
            /*! Renderiza mapa ajustando o movimento.
             Porem o mapa que será renderizado é ajustado de acordo com o movimento informado.
             \param x Posição no eixo x onde o mapa será renderizado.
             \param y Posição no eixo y onde o mapa será renderizado.
             \param width Largura do mapa.
             \param height Altura do mapa.
             \param moveX Movimento que deve ser aplicado no eixo x do mapa que será renderizado.
             \param moveY Movimento que deve ser aplicado no eixo y do mapa que será renderizado.
             */
            virtual void renderPerfect(int x, int y, int width, int height, int moveX, int moveY);
            
            //! Retorna tamanho do mapa em pixels.
            /*! return Tamanho do mapa em pixels. */
            virtual Vector2i getSize();
            
            //! Retorna o tamanho do tile.
            /*! return Tamanho do tile em . */
            virtual Vector2i getTileSize();
            
            //! Retorna o numero de tiles.
            virtual Vector2i getTileNumber();
            
            //Initialize manually the map data
            //! Inicializa manualmente um mapa.
            /*! Inicializa manualmente um mapa.
             \param tileBlock Número de blocos em cada eixo.
             \param tileSize Tamanho em pixels de cada bloco.
             \param path Caminho da imagem que será carregada
             */
            virtual void initializeData(Vector2<int> tileBlock, Vector2<int> tileSize, string path);
            //! Inicializa manualmente um mapa.
            /*! Inicializa manualmente um mapa.
             \param tileBlockX Número de blocos no eixo x.
             \param tileBlockY Número de blocos no eixo y.
             \param tileSizeX Tamanho em pixels do bloco no eixo x.
             \param tileSizeY Tamanho em pixels do bloco no eixo y.
             \param path Caminho da imagem que será carregada
             */
            virtual void initializeData(int tileBlockX, int tileBlockY, int tileSizeX, int tileSizeY, string path);
            
            //Clear the data structure fill it with zero
            //! Preenche toda a estrutura do mapa com o valor 0.
            virtual void clearDataStructure();
            //Clear the data, all the vector data will be wiped and the vector will became invalid
            //! Deleta todos os tiles do mapa e o vetor vira invalido.
            virtual void clearData();
            
            //Clear the data and the structure
            //! Remove os dados, transformando o vetor em um vetor invalidor e apaga o cabeçalho.
            virtual void clear();
            
            //Clear data structure
            //! Adiciona um tile na posição especificada com o valor definido.
            /*! Adiciona um tile na posição especificada com o valor definido.
             \param x Indice no eixo x da matriz de blocos que se deseja alterar o valor do tile.
             \param y Indice no eixo y da matriz de blocos que se deseja alterar o valor do tile.
             \param value Novo valor para o bloco.
             */
            virtual void addTile(int x, int y, int16_t value);
            
            //! Retorna a imagem do tilesheet.
            virtual Core::Image* getImage();
        };
}
#endif /* defined(__Action_Adventure_Game_Engine__TileManager__) */
