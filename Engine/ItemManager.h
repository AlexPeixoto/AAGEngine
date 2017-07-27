//
//  ItemManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/11/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//
//Here i manage the creation of the itens
//I initialize initialize all the itens here and have a pool of those itens.
//Every item have an id and this + location are referenced on the map using the structure ItemRef
//This class is a static one, because i just need to load the itens once

#ifndef __Action_Adventure_Game_Engine__ItemManager__
#define __Action_Adventure_Game_Engine__ItemManager__

#include <iostream>
#include <vector>
#include "LogManager.h"
#include "Item.h"


namespace Adventure{
    //! Gerencia todos os itens.
    class ItemManager{
    private:
        //! Contem lista dos itens carregados.
        static std::vector<Item*>* itemList;
        //! Verifica se já existe um item com a id informada.
        static bool checkIfExists(int id);
    public:
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de itens será o definido no relativePath + nome do arquivo.
        static string relativePath;
        
        
        //! Remove os itens carregados quando o programa terminar.
        ~ItemManager();
        
        //! Renderiza objeto na posição especificada.
        static void render(int id, Point2i position);
        
        //! Retorna o objeto com a id informada.
        static Item* getItem(int id) const;
        //! Carrega Sprite do objeto com a id informada.
        static bool loadSprite(int id);
        //! Carrega objetos a partir do arquivo passado por parametro.
        /*! Carrega objeto contendo a seguinte estrutura.
         Inteiro com a quantidade de objetos. <br />
         Para cada objeto: <br />
         1. Inteiro com a id do objeto. <br />
         2. Inteiro com a largura do objeto. <br />
         3. Inteiro com a altura do objeto. <br />
         4. Char[255] com o caminho da imagem do objeto. <br />
         5. Char[100] com o nome do objeto. <br />
         6. Carrega quantidade de propriedades do objeto. <br />
            6.1 Inteiro contendo tamanho da chave. <br />
            6.2 Char* com a chave. <br />
            6.3 Inteiro contendo tamanho do valor. <br />
            6.4 Char* contendo o valor. <br />
         Nota: Caso o item já tenha sido carregado a id é ignorada.
         \return Retorna se foi possivel abrir o arquivo.
         */

        static bool loadFromFile(std::string&& path);
        //! Descarrega todos os objetos carregados.
        /*! Descarrega todos os objetos carregados tornando os ponteiros retornados invalidos. */
        static void unloadData();
        //! Adiciona ponteiro do objeto informado na lista de warps.
        /*!
         \return Retorna se o objeto passado por parametro ja existe.
         */
        static bool addItem(Item* item);
        //! Inicializa ponto no mapa para warp
        /*!
         \param id ID unica do objeto.
         \param path Caminho da imagem que representa o objeto.
         \param name Nome do objeto.
         \param tileSize Largura e altura do tile do objeto.
         */
        static bool addItem(int id, const std::string& path, const std::string& name, Vector2i tileSize);
        //! Remove objeto com a id informada.
        /*!
         \param id ID do objeto que se deseja remover.
         \return Retorna se foi possivel remover o objeto. Caso a id informada não exista é retornado (false).
         */
        static bool removeItem(int id);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__ItemManager__) */
