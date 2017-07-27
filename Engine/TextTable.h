//
//  TextTable.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/14/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__TextTable__
#define __Action_Adventure_Game_Engine__TextTable__

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

namespace Core{
    //! Classe estática contendo um "dicionário".
    class TextTable{
    private:
        //! Define associação entre chave e texto.
        static std::map<std::string, std::string> text;
    public:
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de texto será o definido no relativePath + nome do arquivo.
        static std::string relativePath;
        //! Carrega arquivo contendo definições de um texto.
        /*! Texto carregado no formato:
         *  Chave:
         *  Texto Texto Texto Texto.
         *  Texto Texto Texto Texto.
         *  EOK
         *  Chave2:
         *  Ao se executar o comando diversas vezes chaves são adicionadas e atualizada, nunca removidas.
         \param path Define o caminho do arquivo a ser carregado
         */
        static void loadFromFile(const std::string& path);
        //! Retorna valor da chave.
        /*! Retorna valor da chave especificada.
         \param key Chave que se deseja acessar o valor.
         \return Texto associado com a chave especificada.
         \throw std::runtime_error
         */
        static std::string getByKey(const std::string& key);
        //! Adiciona uma chave e um texto associado a ela.
        /*! Adiciona uma chave e um texto associado a ela.
         \param key Nome da chave que se deseja adicionar um texto associado.
         \param value Texto a ser associado com a chave especificada.
         \return Retorna se a operação ocorreu com sucesso. <br />
         Retorno (false) ocorre quando a chave especificada ja existe.
         */
        static bool addKeyValue(const std::string& key, const std::string& value);
        //! Atualiza uma chave e o texto associado a ela.
        /*! Atualiza uma chave e o texto associado a ela.
         \param key Nome da chave que se deseja atualizar o texto associado.
         \param value Texto a ser atualizado na chave especificada.
         \return Retorna se a operação ocorreu com sucesso. <br />
         Retorno (false) ocorre quando a chave especificada não existe.
         */
        static bool updateKeyValue(const std::string& key, const std::string& value);
        //! Remove chave e texto da chave especificada.
        /*! Remove a chave e o valor associado a ela do map.
         \param key Chave que deve ser removida.
         \return Retorna se a chave especificada e seu valor foram removidos com sucesso.
         */
        static bool removeKey(const std::string& key);
        //! Remove todos os textos carregados no map.
        static void removeAll();
        //! Retorna todas as associações chave=>valor.
        static std::map<std::string, std::string> getAllKeyValues();
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__TextTable__) */
