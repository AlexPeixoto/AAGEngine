//
//  Dropdown.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Dropdown__
#define __Action_Adventure_Game_Engine__Dropdown__

#include <iostream>
#include "TextControl.h"
#include "BackgroundShape.h"
#include "Location.h"
using namespace Core;
using sf::Color;
namespace Adventure{
    //! Define um dropdown list.
    /*! O tamanho do shape da imagem é definido pelo tamanho do texto. */
    class Dropdown : public Location<int>{
    private:
        //! Objeto que renderiza o texto na tela.
        TextControl* textControl;
        
        //! Define o fundo da caixa de opções.
        BackgroundShape* boxShape;
        //! Define o fundo opção selecionada.
        BackgroundShape* optionShape;
        //! Define o fundo da opção na tela.
        BackgroundShape* menuShape;
        
        //! Define o tamanho da borda do menu de opções.
        int boxBorder;
        //! Espaçamento entre as opções.
        int optionSpacing;
        
        //! Define cor dentro do menu de opções.
        Color menuOptionColor;
        //! Define cor da opção selecionada.
        Color selectedOptionColor;
        
        //! Opções adicionadas.
        vector<string> options;
        //! define o nímero maximo de opções por tela
        int optionsPerScreen;
        //! Tamanho maximo do texto.
        int maxTextHeight;
        //! Tamanho maximo do texto
        int maxTextWidth;
        
        //! Define se o menu esta aberto.
        bool openMenu;
        
        //! Opção selecionada dentro do menu de opções.
        int optionIndex;
        //! Opção que foi selecionada.
        int selectedOptionIndex;
        
        //! Função chamada quando uma opção é selecionada.
        function<void (int, Dropdown*)> callback;
        
    public:
        //! Costrutor padrão deletado.
        Dropdown() = delete;
        //! Construtor que recebe o ponteiro do TextControl do Menu.
        Dropdown(TextControl* textControl, int optionsPerScreen, int boxBorder, int optionSpacing, Point2i position, function<void (int, Dropdown*)> callback);
        //! Remove os shapes
        ~Dropdown();
        
        //! Renderiza o elemento selecionado e o menu.
        virtual void render();
        //! Define o numero maximo de opções na tela.
        virtual void intMaxOptionsPerScreen(int optionsPerScreen);
        
        //! Define estado do menu, aberto ou fechado.
        virtual void setOpenMenu(bool openMenu);
        //! Avança para a proxima opção caso o menu esteja aberto.
        virtual bool next();
        //! Retrocede para a opção anterior caso o menu esteja aberto.
        virtual bool prev();
        //! Seleciona a opção atual, dispara o callback e fecha o menu.
        virtual void selectOption();
        //! Calcula o tamanho do shape do menu.
        virtual void calculateMenuShapeSize();

        
        //! Define o callback para quando uma opção for selecionada.
        virtual void setSelectedCallback(function<void (int, Dropdown*)> callback);
        
        //! Retorna o tamanho do dropdown, sem o tamanho do texto.
        virtual Vector2i getSize();
        
        //! Retorna lista de opções.
        virtual vector<string> getOptions() const;
        
        //! Retorna se omenu está aberto.
        virtual bool getOpenMenu();
        
        //! Define o fundo da caixa de opções.
        virtual void setBoxShape(BackgroundShape* boxShape);
        //! Define o fundo da caixa de opções.
        virtual void setOptionShape(BackgroundShape* optionShape);
        //! Define o fundo da opção na tela.
        virtual void setMenuShape(BackgroundShape* menuShape);
        //! Define cor da opção.
        virtual void setMenuOptionColor(Color color);
        //! Define cor da opção selecionada no menu.
        virtual void setSelectedOptionColor(Color color);
        //! Define o espaçamento entre as opções.
        virtual void setOptionSpacing(int optionSpacing);
        //! Adiciona uma nova opção.
        virtual void addOption(string option);
        
        //! Reetorna o fundo da caixa de opções.
        virtual BackgroundShape* returnBoxShape();
        //! Retorna o fundo da caixa de opções.
        virtual BackgroundShape* returnOptionShape();
        //! Retorna o fundo da opção na tela.
        virtual BackgroundShape* returnMenuShape();
        //! Retorna cor da opção;
        virtual Color getMenuOptionColor();
        //! Retorna cor da opção selecionada.
        virtual Color getSelectedOptionColor();
        //! Retorna a opção no indice especificado.
        virtual string getOption(int index);
        //! Retorna o espaçamento entre as opções.
        virtual int getOptionSpacing();
        
        //! Remove a opção no indice especificado, atualiza os indices.
        virtual bool removeOption(int index);
    };
}

#endif /* defined(__Action_Adventure_Game_Engine__Dropdown__) */
