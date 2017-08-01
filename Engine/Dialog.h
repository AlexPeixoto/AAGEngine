//
//  Dialog.h
//  AAGEngine
//
//  Created by Alex Peixoto on 8/27/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__Dialog__
#define __Action_Adventure_Game_Engine__Dialog__

#include <iostream>
#include <vector>
#include "TextControl.h"
#include "BackgroundShape.h"

using Core::TextControl;
using Core::BackgroundShape;
using sf::Color;
using sf::Uint8;

namespace Adventure{
    /*Was choosen as an design pattern to not have pointers, all the variables are initialized because it is expected that the Dialog class was instanciated to create an dialog with options, if not that could be archived using only the TextControl*/
    /*The option and text font size are the same */
    /*As an Engine limitation the options do not break line*/
    //! Define classe para dialogos.
    /*!
     Implementa caixas de diálogo.
     Classes de dialogo são utilizadas para representar conversas dentro de um jogo, menu de opções, compras de itens e qualquer funcionalidade que necessite de um menu de opções.
     */
    class Dialog{
    protected:
        //! Ponteiro para qual tela deve ser efetuada a chamada de render pela classe Text.
        static sf::RenderWindow* window;
        //! Indice de qual texto está sendo renderizado.
		size_t speechIndex;
        //! Indice de qual parte do texto está sendo renderizado.
		size_t speechScreenIndex;
        //! Indice da pergunta.
        size_t questionIndex;
        //! Indice da opção marcada na pergunta.
		size_t optionIndex;
        //! Tamanho da borda da caixa de dialogo contendo o texto da conversa.
        int speechInnerBorder;
        //! Tamanho da borda da caixa de dialogo contendo o texto da opção.
        int optionInnerBorder;
        //! Define se alguma pergunta esta sendo renderizada no momento
        bool renderingQuestion;
        
        //Stores the text max height when the font is loaded
        //! Altura maxima da fonte.
        /*!
         Define o altura maxima da fonte.
         Para isto no construtor alguns caracteres da fonte são analizados e o maior e definido como altura maxima da fonte.
         */
        int textHeight;
        
        //! Define cor do texto da conversa.
        Color speechColor;
        //! Define cor do texto da pergunta.
        Color questionColor;
        //! Define cor do texto da opção.
        Color optionColor;
        
        //! Ponteiro do TextControl.
        /*!
         Todas as manipulações referentes ao tamanho do texto, conteudo e divisão do mesmo em telas é feita pelo TextControl.
         */
        TextControl* textControl;
        
        //! Estrutura que define em qual texto deve aparecer uma pergunta.
        typedef struct DialogHandle{
            int speechId; //*!< Id do texto. */
            int questionIndex; /*!< Indice da pergunta. */
        } DialogHandle;
        
        //! Define uma opção dentro de uma pergunta.
        typedef struct Option{
            int id; /*!< Id da opção. */
            std::string text; /*!< Texto da opção. */
        } Option;
        
        //! Define uma pergunta.
        typedef struct Question{
            int id; /*!< Id da pergunta. */
            std::string title; /*!< Titulo da pergunta. */
            std::function<void(int, int, int, Dialog*)> func; /*!< Ponteiro para função de callback da pergunta. */
            std::vector<Option> options; /*!< Opções da pergunta. */
            int widestSize; /*!< Largura da maior opção na pergunta. */
        } Question;
        
        //! Define um texto de uma conversa.
        typedef struct Speech{
            int id; /*!< Id do texto. */
            std::string speech; /*!< Texto. */
            bool isEnd; /*!< Define se após este texto o dialog deve ser encerrado. */
        } Speech;
        //! Define fundo do texto.
        BackgroundShape *speechBoxShape;
        //! Define fundo da pergunta.
        BackgroundShape *questionBoxShape;
        //! Defune fundo da opção.
        BackgroundShape *optionShape;
        
        //Vector of each text, so if i have dialogBoxSize variation the TextControl handles that.
        //! Vetor contendo cada um dos textos.
        std::vector<Speech> speeches;
        
        //Maps after what text i should present a dialog
        //! Vetor mapeando a associação de cada texto com uma pergunta.
		std::vector<DialogHandle> dialogToQuestion;
        //first => ID, second => Text
        //! Vetor de perguntas.
		std::vector<Question> questions;
        
        //DialogBox and OptionBox Position
        //! Posição da caixa de dialogo.
        Point2i dialogBoxPosition;
        //! Posição da pergunta.
        Point2i questionBoxPosition;
        
        //DialogBox and OptionBox sizes
        //! Tamanho da caixa de dialogo.
        Vector2i dialogBoxSize;
        //! Tamanho da caixa de pergunta.
        Vector2i questionBoxSize;
        
        //If this one is true the option box is calculated on real time when the options are picked
        //! Define se o tamanho da caixa de opções deve ser calculado pelo tamanho da maior opção.
        bool optionBoxByLargest;
        
        //! Retorna iterator para a opção com o id especificado.
		std::vector<Question>::iterator getQuestion(int id) const;
        
        //! Retorna, dentro de um vetor de opções, o tamanho da maior opção.
        int getWidestOptionSize(std::vector<Option> options) const;
        
    public:
        //! Remove construtor padrão.
        Dialog() = delete;
        //! Inicializa dialogo.
        /*! Inicializa dialogo:
            1. Carrega fonte no caminho definido.
            2. Calcula tamanho do maior caracter.
            3. Define a escala do texto como 50%.
            4. Define o espaçamento entre textos como 5 pixels.
            5. Define a cor de todos os textos como R=100, G=100, B=100, A-255.
            6. Invalida o tamanho da caixa do texto, pergunta e opção.
         */
        Dialog(const std::string& font);
        //! Descarrega fonte.
        ~Dialog();
        //function receives the speech id, question id, option id, and an pointer of the dialog
        //! Adiciona uma nova pergunta.
        /*! Adiciona uma nova pergunta e define a função de callback a ser chamada para esta pergunta quando uma opção for selecionada.
         \param id ID da pergunta.
         \param title Titulo da pergunta.
         \param func Contem a função de callback da pergunta que será chamada quando uma opção for selecionada. Os parametros recebidos serão Id do texto, Id da pergunta, Id da opção e ponteiro para o dialogo.
         \return Retorna se a pergunta foi adicionada. Caso ja exista uma pergunta com a id informada é retornado (false).
         */
        bool addQuestion(int id, const std::string& title, std::function<void(int, int, int, Dialog*)> func);
        //! Remove uma pergunta com a id especificada.
        /*! Remove uma pergunta com a id especificada.
         \param id Id da pergunta a ser removida.
         \return Retorna se a pergunta foi removida. Caso não exista uma pergunta com a id informada é retornado (false).
         */
        bool removeQuestion(int id);
        //Adds an option to a question
        //question index, id
        //! Adiciona uma nova opção.
        /*! Adiciona uma nova opção na pergunta com a id especificada.
         \param questionId Id da pergunta que se deseja adicionar a opção.
         \param id Id da opção que esta sendo adicionada.
         \param option Texto da opção.
         \return Retorna se a opção foi adicionado. Caso ja exista uma opção com a id informada é retornado (false).
         \throw runtime_error.
         */
        bool addOption(int questionId, int id, const std::string& option);
        //! Remove uma opção com a id especificada.
        /*! Remove uma opção com a id especificada.
         \param questionId Id da pergunta que se deseja remover uma opção.
         \param id Id da opção a ser removida.
         \return Retorna se a opção foi removida. Caso não exista uma pergunta com a id informada é retornado (false).
         */
        bool removeOption(int questionId, int id);
        //! Adiciona uma associação entre um texto e uma pergunta.
        /*!
         \return Retorna se foi possivel adicionar um novo DialogHandle. Caso um texto com a id informada já exista é retornado (false).
         */
        bool addDialogHandle(DialogHandle dh);
        //! Adiciona uma associação entre um texto e uma pergunta.
        /*!
         \return Retorna se foi possivel adicionar um novo DialogHandle. Caso um texto com a id informada já exista é retornado (false).
         */
        bool addDialogHandle(int speechId, int questionId);
        //! Remove associação entre um texto e uma pergunta.
        void removeDialogHandle(int id);

        //! Renderiza texto.
        void renderSpeech();
        //! Altera id do texto que deve ser renderizado.
        /*! Altera id do texto que deve ser renderizado.
         \return Retorna se foi possivel adicionar um novo texto. Caso o texto ja exista é retornado (false).
         */
        bool gotoSpeech(int id);
        //! Retorna para o texto anterior.
        /*!
         Verifica se o texto contem diversas telas.
         Se ele conter diversas telas é retornado para a tela anterior.
         \return Retorna se foi possivel retornar para a tela ou texto anterior. Caso o indice da tela e do texto sejam zero é retornado (false). Caso se esteja renderizando uma pergunta é retornado false.
         */
        bool prevSpeech();
        //! Avança para o texto anterior.
        /*!
         Verifica se o texto contem diversas telas.
         Se ele conter diversas telas é avançado para a tela posterior.
         \return Retorna se foi possivel avançar para a proxima tela ou texto. Caso o indice da tela e do texto se encontrem no limite é retornado (false). Caso se esteja renderizando uma pergunta é retornado false.
         */
        bool nextSpeech();
        //! Retorna a id do texto atual.
        int getSpeechId() const;
        
        //Check if the current text have a question associated to it
        //! Retorna se existe alguma pergunta associada ao texto atual.
        bool haveQuestion();
        //! Renderiza pergunta.
        void renderQuestion();
        //! Retorna id da pergunta.
        int getQuestionId() const;
        
        //! Define se deve-se renderizar uma pergunta.
        void setRenderingQuestion(bool renderingQuestion);
        //! Retorna se deve-se renderizar uma pergunta.
        bool getRenderingQuestion() const;
        
        //Select next option on the active question
        //! Seleciona a proxima pergunta da pergunta atual.
        /*! Seleciona a proxima pergunta da pergunta atual.
         \return Retorna se foi possivel avançar a pergunta. Caso a posição atual seja a ultima pergunta é retornado (false).
         */
        bool nextOption();
        //! Seleciona a pergunta anterior a pergunta atual.
        /*! Seleciona a pergunta anterior a pergunta atual.
         \return Retorna se foi possivel retroceder a pergunta. Caso a posição atual seja a primeira pergunta é retornado (false).
         */
        bool prevOption();
        //! É executado o functor para a pergunta passando a opção atual como parametro
        void selectOption();
        //! Retorna a id da opção selecionada.
        int getOptionId() const;
        
        //! Define a cor/borda de fundo do texto.
        void setSpeechBoxShape(BackgroundShape* speechBoxShape);
        //! Retorna a cor/borda de fundo do texto.
        BackgroundShape* getSpeechBoxShape();
        
        //! Define o a cor/borda de fundo da pergunta.
        void setQuestionBoxShape(BackgroundShape* questionBoxShape);
        //! Retorna a cor/borda de fundo da pergunta.
        BackgroundShape* getQuestionBoxShape() const;
        
        //! Define o a cor/borda de fundo da opção.
        void setOptionShape(BackgroundShape* optionShape);
        //! Retorna a cor/borda de fundo da opção.
        BackgroundShape* getOptionShape() const;
        
        //To manage the sizes
        //! Define a escala da fonte.
        void setFontScale(float scale);
        //! Retorna a escala da fonte.
        float getFontScale() const;
        
        //! Define a tela onde esta sendo renderizado o texto.
        void static setWindow(sf::RenderWindow *window);
        
        //! Adiciona novo Speech.
        /*! Adiciona novo texto contendo: <br />
            1. Id do texto. <br />
            2. Texto. <br />
            3. Booleana definindo se após este texto deve-se terminar o dialogo.
            \return Retorna se foi possivel adicionar o novo texto. Caso a id do texto ja exista é retornado (false).
         */
        bool addSpeech(Speech speech);
        //! Adiciona novo texto.
        /*!
         \param id Id do texto.
         \param speech Texto.
         \param isEnd definindo se após este texto deve-se terminar o dialogo.
         \return Retorna se foi possivel adicionar o novo texto. Caso a id do texto ja exista é retornado (false).
         */
        bool addSpeech(int id, const std::string& speech, bool isEnd);
        //! Remove texto com a id especificado.
        /*! Remove texto com a id especificado.
         \param id Id do texto que ser;a removido.
         */
        bool removeSpeech(int id);
        //! Retorna Speech com a id informada.
        /*! Retorna Speech com a id informada.
         \return Retorna speech com a id informada. Caso não encontrar nenhum Speech com a id informada é retornado um Speech com a id=-1.
         */
        Speech getSpeech(int id) const;
        
        //! Define o tamanho da caixa de dialogo.
        void setDialogBoxSize(Vector2i size);
        //! Define o tamanho da caixa de dialogo.
        void setDialogBoxSize(int width, int height);
        
        //! Retorna a largura da caixa de dialogo.
        int getDialogBoxWidth() const;
        //! Retorna a altura da caixa de dialogo.
        int getDialogBoxHeight() const;
        //! Retorna o tamanho da caixa de dialogo.
        Vector2i getDialogBoxSize() const;
    
        //! Define a posiç!ao da caixa de dialogo.
        void setDialogBoxPosition(Point2i position);
        //! Define a posiç!ao da caixa de dialogo.
        void setDialogBoxPositon(int x, int y);
        
        //! Retorna a posição da caixa de dialogo no eixo X.
        int getDialogBoxX() const;
        //! Retorna a posição da caixa de dialogo no eixo Y.
        int getDialogBoxY() const;
        //! Retorna a posição da caixa de dialogo.
        Point2i getDialogBoxPosition() const;
        
        //! Define o tamanho da caixa que contem a pergunta.
        void setQuestionBoxSize(Vector2i size);
        //! Define o tamanho da caixa que contem a pergunta.
        void setQuestionBoxSize(int width, int height);
        
        //! Retorna a largura da caixa que contem a pergunta.
        int getQuestionBoxWidth() const;
        //! Retorna a altura da caixa que contem a pergunta.
        int getQuestionBoxHeight() const;
        //! Retorna o tamanho da caixa que contem a pergunta.
        Vector2i getQuestionBoxSize() const;
        
        //! Define a posição da caixa de pergunta.
        void setQuestionBoxPosition(Point2i position);
        //! Define a posição da caixa de pergunta.
        void setQuestionBoxPositon(int x, int y);
        
        //! Retorna a posiçãp da caixa de pergunta no eixo X.
        int getQuestionBoxX() const;
        //! Retorna a posiçãp da caixa de pergunta no eixo Y.
        int getQuestionBoxY() const;
        //! Retorna posição da caixa de pergunta.
        Point2i getQuestionBoxPosition() const;
        
        //! Define se o tamanho da opção deve ser o tamanho da maior opção no vetor.
        void setQuestionBoxByLargest(bool largest);
        //! Retorna se o tamanho da opção deve ser o tamanho da maior opção no vetor.
        bool getQuestionBoxByLargest() const;
        
        //! Define o tamanho da borda interna do texto.
        void setSpeechInnerBorder(int speechInnerBorder);
        //! Retorna o tamanho da borda interna do texto.
        int getSpeechInnerBorder() const;
        
        //! Define o tamanho da borda interna da opção.
        void setOptionInnerBorder(int optionInnerBorder);
        //! Retorna o tamanho da borda interna da opção.
        int getOptionInnerBorder() const;
        
        //! Define a cor da fonte do texto.
        void setSpeechColor(Color speechColor);
        //! Define a cor da fonte do texto.
        void setSpeechColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        //! Retorna a cor da fonte do texto.
        Color getSpeechColor() const;
        
        //! Define a cor da fonte da pergunta.
        void setQuestionColor(Color questionColor);
        //! Define a cor da fonte da pergunta.
        void setQuestionColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        //! Retorna a cor da fonte da pergunta.
        Color getQuestionColor() const;
        
        //! Define a cor da fonte da opção.
        void setOptionColor(Color optionColor);
        //! Define a cor da fonte da opção.
        void setOptionColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        //! Retorna a cor da fonte da opção.
        Color getOptionColor() const;
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__Dialog__) */
