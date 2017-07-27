//
//  WarpManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__WarpManager__
#define __Action_Adventure_Game_Engine__WarpManager__

#include <iostream>
#include <vector>
#include <random>
#include "LogManager.h"
#include "Warp.h"

namespace Adventure{
    //! Gerencia todos os warps no mapa.
    class WarpManager{
    private:
        //! Contem lista dos warps carregados.
        static std::vector<Warp*>* warpList;
        //! Verifica se já existe um warp com a id informada.
        static bool checkIfExists(int id);
    public:
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de warp será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        
        //! Remove os warps carregados quando o programa fechar
        ~WarpManager();
        
        //! Retorna o warp com a id informada.
        static Warp* getWarp(int id);
        
        //! Carrega warps a partir do arquivo passado por parametro.
        /*! Carrega warp contendo a seguinte estrutura.
            Inteiro com a quantidade de warps. <br />
            Para cada warp: <br />
                1. Inteiro com a id do warp. <br />
                2. Inteiro com a largura do warp. <br />
                3. Inteiro com a altura do warp. <br />
                3. Char[255] com o destino do warp. <br />
                4. Char[100] com o nome do warp. <br />
                5. Inteiro com a posição X de destino do warp. <br />
                6. Inteiro com a posição Y de destino do warp.
         */
        static bool loadFromFile(const std::string& path);
        //! Descarrega todos os warps carregados.
        /*! Descarrega todos os warps carregados tornando os ponteiros retornados invalidos. */
        static void unloadData();
        //! Adiciona ponteiro do Warp informado na lista de warps.
        /*!
         \return Retorna se o Warp passado por parametro ja existe.
         */
        static bool addWarp(Warp* warp);
        //! Cria novo Warp e adiciona na lista de warps.
        /*!
         \param id ID unica do warp.
         \param path Caminho onde se encontra arquivo que deve ser carregado ao se colidir com um warp.
         \param name Nome do warp.
         \param size Altura e largura do warp.
         \param destiny Posição x e y onde o personagem deve aparecer no mapa carregado.
         \return Retorna se foi possivel adicionar o warp. Caso a id informada já exista é retornado (false).
         */
        static bool addWarp(int id, const std::string& path, const std::string& name, Point2i size, Point2i destiny);
        //! Remove warp com a id informada.
        /*! 
         \param id ID do warp que se deseja remover.
         \return Retorna se foi possivel remover o warp. Caso a id informada não exista é retornado (false).
         */
        static bool removeWarp(int id);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__WarpManager__) */
