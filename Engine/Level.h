//
//  Level.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Level__
#define __Action_Adventure_Game_Engine__Level__

#include <iostream>

namespace Adventure{
    //! Define classe base que será carregada pelo LevelManager.
    class Level{
    public:
        Level();
        virtual ~Level();
        //! Define metodo de render.
        virtual void render();
        //! Define metodo de processamento.
        virtual void process();        
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Level__) */
