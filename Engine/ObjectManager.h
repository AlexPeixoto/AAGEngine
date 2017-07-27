//
//  ObjectManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/31/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__ObjectManager__
#define __Action_Adventure_Game_Engine__ObjectManager__

#include <iostream>
#include <vector>
#include <random>
#include "LogManager.h"
#include "Object.h"

using std::vector;

namespace Adventure{
    class ObjectManager{
    private:
        //! Contem lista dos objetos carregados.
        static vector<Object*>* objectList;
        //! Verifica se já existe um objeto com a id informada.
        static bool checkIfExists(int id);
    public:
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de objects serão o definido no relativePath + nome do arquivo.
        static string relativePath;
        
        //! Remove os objetos carregados quando o programa terminar.
        ~ObjectManager();
        
        //! Renderiza objeto na posição especificada.
        static void render(int id, Point2i position);
        
        //! Retorna o objeto com a id informada.
        static Object* getObject(int id);
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
         7. Quantidade de itens do objeto. <br />
            7.1 Inteiro contendo a o id do item. <br />
            7.2 Quantidade do item.
            Nota: Caso o item não tenha sido carregado a id é ignorada.
         Nota: Caso o objeto já tenha sido carregado a id é ignorada.
         \return Retorna se foi possivel abrir o arquivo.
         */
        static bool loadFromFile(string path);
        //! Descarrega todos os objetos carregados.
        /*! Descarrega todos os objetos carregados tornando os ponteiros retornados invalidos. */
        static void unloadData();
        //! Adiciona ponteiro do objeto informado na lista de warps.
        /*!
         \return Retorna se o objeto passado por parametro ja existe.
         */
        static bool addObject(Object* object);
        //! Inicializa ponto no mapa para warp
        /*!
         \param id ID unica do objeto.
         \param path Caminho da imagem que representa o objeto.
         \param name Nome do objeto.
         \param tileSize Largura e altura do tile do objeto.
         \param randomize Se o item a ser retornado deve ser randomizado.
         */
        static bool addObject(int id, string path, string name, Vector2i tileSize, bool randomize);
        //! Remove objeto com a id informada.
        /*!
         \param id ID do objeto que se deseja remover.
         \return Retorna se foi possivel remover o objeto. Caso a id informada não exista é retornado (false).
         */
        static bool removeObject(int id);
        
        //! Retorna randomicamente um item do objeto correspondente a id informada.
        static int getRandomItem(int id);
        
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__ObjectManager__) */
