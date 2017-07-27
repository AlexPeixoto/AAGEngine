//
//  SoundEffect.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/25/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__SoundEffect__
#define __Action_Adventure_Game_Engine__SoundEffect__

#include <iostream>

using namespace std;

namespace Adventure{
    class SoundEffectManager;
    //! Define efeito sonoro que irá tocar no mapa.
    class SoundEffect{
        friend class SoundEffectManager;
    private:
        //! Define a id do som
        int id;
        //! Define o caminho do rquivo de som.
        string path;
        //! Define o nome do som.
        string name;
        //Area that the sound is player with full volume
        //! Distancia minima, em pixels, do som no qual pode-se ouvi-lo com 100% de volume.
        int minPixelDistance;
        //Sound reduction per pixel (euclidean distance) after surpass the minPixelDistance
        //! Redução do som por pixel depois de se distanciar do valor definido pelo minPixelDistance.
        float attenuation;
        //Space from the point on the map (as the center) on each direction that the sound is played as stereo:
        //If i set 50 it is fro (-50, -50) up to (50, 50).
        //! Area na qual pode-se ouvir o som em ambos os canais de som.
        int bothSpeakersArea;
        
    public:
        //! Construtor utilizado pelo SoundEffectManager.
        SoundEffect();
        //! Inicializa o efeito sonoro.
        /*! Inicializa o efeito sonoro.
         \param id Id do efeito sonoro.
         \param path Caminho do arquivo do efeito sonoro.
         \param name Nome do efeito sonoro.
         \param minPixelDistance Distancia minima em pixels no qual pode-se ouvir o som com 100% do volume.
         */
        SoundEffect(int id, string path, string name, int minPixelDistance);
        //! Remove o som da memória.
        ~SoundEffect();
        
        //! Retorna id do efeito sonoro.
        virtual int getID();
        
        //! Retorna caminho do arquivo do efeito sonoro.
        virtual string getPath() const;
        //! Define caminho do arquivo do efeito sonoro.
        virtual void setPath(string path);
        
        //! Retorna o nome do efeito sonoro.
        virtual string getName() const;
        //! Define o nome do efeito sonoro.
        virtual void setName(string name);
        
        //! Retorna distancia minima na qual se pode ouvir o som com 100% de volume.
        virtual int getMinPixelDistance();
        //! Define distancia minima na qual se pode ouvir o som com 100% de volume.
        virtual void setMinPixelDistance(int minPixelDistance);
        
        //! Retorna atenuação sonora após se exceder o minPixelDistance.
        virtual float getAttenuation();
        //! Define atenuação sonora após se exceder o minPixelDistance.
        virtual void setAttenuation(float attenuation);
        
        //! Retorna área na qual se é possivel ouvir o som em ambos os canais de som.
        virtual int getBothSpeakersArea();
        //! Define área na qual se é possivel ouvir o som em ambos os canais de som.
        virtual void setBothSpeakersArea(int bothSpeakersArea);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__SoundEffect__) */
