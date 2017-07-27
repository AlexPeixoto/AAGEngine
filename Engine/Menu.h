//
//  Menu.h
//  AAGEngine
//
//  Created by Alex Peixoto on 9/24/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Menu__
#define __Action_Adventure_Game_Engine__Menu__

#include <iostream>
#include <vector>
#include "Checkbox.h"
#include "Information.h"
#include "InformationImage.h"
#include "Slidebar.h"
#include "Dropdown.h"
#include "Selectable.h"

using namespace std;

namespace Adventure{
    class Menu{
    public:
        //! Define os tipos de elementos que podem ser adicionados no menu
        enum TYPES{
            CHECKBOX, /*!< Checkbox. */
            DROPDOWN, /*!< Drop down line. */
            SLIDEBAR, /*!< Barra, comumente para selecionar entre valores como (0 - 255). */
            INFORMATION, /*!< Linha com texto informativo. */
            INFORMATIONIMAGE, /*!< Imagem com um texto associado. */
            SELECTABLE /*!< Conjunto de imagens selecionaveis. */
        };
    private:
        typedef struct Element{
            int type;
            int index;
        } Element;
        
        //! Vetor de dropdown.
        vector<Dropdown*> dropdowns;
        //! Vetor de checkbox.
        vector<Checkbox*> checkboxes;
        //! Vetor de informações.
        vector<Information*> informations;
        //! Vetor de imagens informativas.
        vector<InformationImage*> informationimage;
        //! Vetor de slidebars.
        vector<Slidebar*> slidebars;
        //! Vetor de itens selecionaveis.
        vector<Selectable*> selectables;
        
        //! Vetor que mapeia o elemento com o indice real dentro.
        vector<Element*> elements;
        
        //! Utilizado para renderizar os textos na tela.
        TextControl* textControl;
    public:
        //! Remove construtor padrão.
        Menu() = delete;
        //! Inicializa menu definindo sua fonte.
        Menu(string font);
        
        //! Renderiza todos os itens.
        virtual void render();
        
        //! Adiciona novo checkbox.
        /*! Adiciona novo checkbox.
         \param checkbox Ponteiro para um checkbox ja inicializado.
         */
        virtual void addCheckbox(Checkbox* checkbox);
        //! Adiciona novo checkbox.
        /*! Adiciona novo checkbox.
         \param text Texto que será exibido junto ao checkbox.
         \param backgroundPath Caminho da imagem que representa o checkbox na tela quando o checkbox não esta selecionado.
         \param selectionPath Caminho da imagem que representa o checkbox na tela quando o checkbox esta selecionado.
         \param position Posição do checkbox na tela.
         \param textPosition Posição do texto na tela.
         \param color Cor do texto.
         \param callback Função que será executada quando o checkbox for marcado ou desmarcado.
         */
        virtual void addCheckbox(string text, string backgroundPath, string selectionPath, Point2i position, Point2i textPosition, Color color, function<void (bool, Checkbox*)> callback);
        
        //! Adiciona nova informação.
        /*! Adiciona nova informação.
         \param information Ponteiro para uma informação ja inicializada.
         */
        virtual void addInformation(Information* information);
        //! Adiciona nova informação.
        /*! Adiciona nova informação.
         \param information Texto que será exibido na tela.
         \param scale Escala do texto que será exbibido na tela.
         \param position Posição do texto na tela.
         \param Cor do texto na tela.
         */
        virtual void addInformation(string information, Vector2f scale, Point2i position, Color color);
        
        //! Adiciona nova imagem contendo uma informação.
        virtual void addInformationImage(InformationImage* informationImage);
        //! Adiciona nova imagem contendo uma informação.
        virtual void addInformationImage(string imagePath, string text, Point2i imagePosition, Point2i textPosition, Vector2f imageScale, Vector2f textScale, Color textColor);
        
        //! Adiciona uma nova barra de slide.
        virtual void addSlidebar(Slidebar* slidebar);
        //! Adiciona uma nova barra de slide.
        virtual void addSlidebar(string slideBarPath, string slideElementPath, int minValue, int maxValue, int increaseValue, int valuePerPixel, Point2i position, function<void (int value)> callback);

        //! Adiciona uma nova lista de itens selecionaveis.
        virtual void addSelectable(int numberOfItens, int spacing, BackgroundShape* selectedItem, Vector2i itemSize, Point2i position, function<void (int, Selectable*)> callback);
        //! Adiciona uma nova lista de itens selecionaveis.
        virtual void addSelectable(Selectable* selectable);
        
        //! Adiciona um novo dropdown.
        virtual void addDropdown(Dropdown* dropdown);
        //! Adiciona um novo dropdown.
        virtual void addDropdown(int optionsPerScreen, int boxBorder, int optionSpacing, Point2i position, function<void (int, Dropdown*)> callback);
        
        //! Remove elemento utilizando o vetor de elements.
        /*! Os indices são mantidos e o ponteiro vira nullptr. */
        virtual bool removeElement(int index, bool deletePointer=true);
        
        //! Retorna todas as associações elementos->tipo
        virtual std::vector<Element*> getElements() const;
        
        //! Retorna todos os checkboxes.
        virtual std::vector<Checkbox*> getCheckboxes() const;
        
        //! Retorna todas as informações.
        virtual std::vector<Information*> getInformations() const;
        
        //! Retorna todas as imagens com informações.
        virtual std::vector<InformationImage*> getInformationImages() const;
        
        //! Retorna todas as slidebars.
        virtual std::vector<Slidebar*> getSlidebars() const;
        
        //! Retorna todos os dropdowns.
        virtual std::vector<Dropdown*> getDropdowns() const;
        
        //! Retorna todos os itens selecionaveis.
        virtual std::vector<Selectable*> getSelectables() const;
        
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__Menu__) */
