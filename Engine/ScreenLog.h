//
//  ScreenLog.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__ScreenLog__
#define __Action_Adventure_Game_Engine__ScreenLog__

#include <iostream>
#include "Point.h"
#include "TextControl.h"
#include "Location.h"

using Core::Location;
using sf::Point2i;
using Core::TextControl;
namespace Debug{
    //! Classe responsável pela exibição de logs na tela.
    class ScreenLog : public TextControl, public Location<int>{
    protected:
        //! Contem toda a log
        string contentLog;
        //! Conversor de qualquer tipo para string
        stringstream ss;
        //Representa o indice da tela que desejo renderizar, -1 significa a ultima
        int index;
    public:
        //! Construtor da classe, a mesma deve ser iniciada já com a fonte definida.
        ScreenLog(string font="");
        //! Destrutor da classe.
        ~ScreenLog();
        
        //! Metodo para troca de tela
        /*!
         Troca para a tela especificada
         \param index define o indice da tela para o qual se deseja ir
         \return retorna false se o indice for inválido
         */
        bool gotoScreen(int index);
        //! Metodo para avançar para a tela seguinda
        /*!
         \return retorna falso caso não seja possivel avançar
         */
        bool next();
        //! Metodo para retornar para a tela seguinda
        /*!
         \return retorna falso caso não seja possivel retornar
         */
        bool prev();
        //! Metodo que define a tela ativa como a ultima.
        void last();
        
        //! Metodo para renderizar a tela no local definido
        void render();
        //! Metodo "dummy" para chamadas dentro do LogManager
        void flush();

		//! Metodo para executar a divisão correta de telas
		void splitInScreens();
        
        //! Operador (operator<<) para receber mensagens por sobrecarga
        /*!
         Operador uilizado pelo LogManager devido aos templates do tipo ofstream. <br />
         O mesmo não executa nenhuma operação.
         */
        template<typename T>
        friend void operator<<(ScreenLog& sl, T data);
    };
    
    template<typename T>
    void operator<<(ScreenLog& sl, T data){
        sl.ss << data << " ";
        sl.contentLog+=sl.ss.str();
        sl.ss.str("");
        sl.setText(sl.contentLog);
        //sl.splitInScreens(sl.size.x, sl.size.y);
    }
}

#endif /* defined(__Action_Adventure_Game_Engine__ScreenLog__) */
