//
//  SoundEffectManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__SoundEffectManager__
#define __Action_Adventure_Game_Engine__SoundEffectManager__

#include <iostream>
#include <algorithm> 
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundEffect.h"

using std::vector;
using std::for_each;
using sf::Sound;
using sf::SoundBuffer;

namespace Adventure{
    //! Gerencia todos os sound effects no mapa.
    class SoundEffectManager{
    private:
        //! Contem lista dos sound effects carregados.
        static vector<SoundEffect*>* sfxList;
        //! Verifica se já existe um soundeffect com a id informada.
        static bool checkIfExists(int id);
    public:
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de sound effects será o definido no relativePath + nome do arquivo.
        static string relativePath;
        
        //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de instancias de sound effects será o definido no relativePath + nome do arquivo.
        static string relativeInstancePath;
        
        //! Remove os sound effects carregados quando o programa fechar
        ~SoundEffectManager();
        //! Retorna uma instancia de Sound correspondente ao id informado.
        /*! Retorna uma instancia de Sound correspondente ao id informado.
         \return Retorna a instancia correspondente ao id informado ou nullptr caso a id seja invalida.
         \throw std::runtime_error
         */
        static Sound* createInstance(int id);
        //! Retorna o SoundEffect correspondente ao id informado.
        /*! Retorna o SoundEffect correspondente ao id informado.
         \return Retorna a instancia correspondente ao id informado ou nullptr caso a id seja invalida.
         */
        static SoundEffect* getSoundEffect(int id);
        //! Carrega sons a partir do arquivo passado por parametro.
        /*! Carrega sons contendo a seguinte estrutura.
         Inteiro com a quantidade de sons. <br />
         Para cada objeto: <br />
         1. Inteiro com a id do som. <br />
         2. Inteiro com a distancia minima para se ouvir o som em ambos os canais de som. <br />
         3. Inteiro com a atenuação utilizada para aumentar/diminuir o volume ao se aproximar/distanciar do som. <br />
         4. Inteiro com a distancia em que se pode ouvir o som em ambos os canais. <br />
         5. Char[255] com o caminho do arquivo de som. <br />
         6. Char[100] com o nome do som. <br />
         Nota: Caso o som já tenha sido carregado a id é ignorada.
         \return Retorna se foi possivel abrir o arquivo.
         */
        static bool loadFromFile(string path);
        //! Descarrega todos os sons carregados.
        /*! Descarrega todos os sons carregados tornando os ponteiros retornados invalidos. */
        static void unloadData();
        //! Adiciona ponteiro do SoundEffect informado na lista de warps.
        /*!
         \return Retorna se o SoundEffect passado por parametro ja existe.
         */
        static bool addSoundEffect(SoundEffect* soundEffect);
        //! Cria novo SoundEffect e adiciona na lista de SoundEffects
        /*!
         \param id ID unica do sound effect.
         \param path Caminho onde se encontra arquivo de som.
         \param name Nome do warp.
         \param maxPixelDistance Distancia maxima, em pixels, da qual se pode ouvir o som com 100% de volume.
         \return Retorna se foi possivel remover o sound effect. Caso a id informada já exista é retornado (false).
         */
        static bool addSoundEffect(int id, string path, string name, int maxPixelDistance);
        //! Remove SoundEffect com a id informada.
        /*!
         \param id ID do sound effect que se deseja remover.
         \return Retorna se foi possivel remover o sound effect. Caso a id informada não exista é retornado (false).
         */
        static bool removeSoundEffect(int id);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__SoundEffectManager__) */
