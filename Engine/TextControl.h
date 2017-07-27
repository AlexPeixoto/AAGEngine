//
//  TextControl.h
//  AAGEngine
//
//  Created by Alex Peixoto on 7/21/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//
//

#ifndef _TextControl
#define _TextControl
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include "Game.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;
using sf::Vector2f;
using sf::Vector2i;
using sf::Font;
using sf::Text;
using sf::RenderWindow;
using sf::Uint8;
using sf::Point2i;
using sf::Color;
namespace Core{
	//class StartEnd;
	class TextControl
		{
		protected:
            //! Guarda todo o texto.
			string text;
            //! Guarda lista de palavras.
			vector<string> word;
            //! Guarda uma linha contendo a maior quantidade de palavras possiveis dentro de uma linha, respeitando a largura da tela.
			vector<string> line;
            //! Contem os indices de linhas <inicio, fim> que serão exibidas por tela, respeitando a altura definida.
			vector<pair<int, int>> screen;

            //! Caminho da fonte.
            string fontPath;
            //! Fonte que sera carregada para exibir o texto e que será utilizada para se calcular altura/largura dos textos.
			Font* font;
            //! Classe de texto, o qual carrega a fonte e pode renderizar o texto na tela..
			Text* textRender;
            //! Espaçamento entre as lihas.
            int textSpacing;
            
            //! Escala da fonte, normal é 1.0.
            Vector2f fontScale;
            
            //! Ponteiro para qual tela deve ser efetuada a chamada de render pela classe Text.
            static RenderWindow *window;
            
            //! Divide o texto em palavras.
            virtual void splitInWords();
            //! Divide o texto em linhas, respeitando a largura definida.
			virtual void splitInLines(int width);
            
            //! Apaga todas as linhas.
            virtual void clearLines();
            //! Apaga todas as palavras.
            virtual void clearWords();
            
		public:
            //! Define um caminho relativo, caso seja inicializado com um valor diferente de vazio o caminho para o carregamento de arquivos de fontes será o definido no relativePath + nome do arquivo.
            static string relativePath;
            
            //! Inicializa estrutura basica do TextControl.
			TextControl();
            //! Inicializa fonte e texto do TextControl, chamando o construtor TextControl por <i> Constructor Delegation</i>.
			TextControl(string path, string text="");
			
            //! Destroi todos os objetos do TextControl invalidando assim todas as telas de texto geradas.
			~TextControl();
			
            //! Divide o texto em telas.
            /*! Divide o texto em telas (conjunto de linhas. <br />
                O processo chama automaticamente: <br />
                <p>    splitInWords;</p>
                <p>    splitInLines;</p>
                A altura define quantas linhas poderão aparecer por tela, sendo calculado a (linha + espaçamento entre linhas)/tamanho informado
                \param width Define a largura do texto que será exibido.
                \param height Define a altura do texto que será exibido.
             */
             
			virtual void splitInScreens(int width, int height);
            //! Divide o texto em telas.
            /*! Divide o texto em telas (conjunto de linhas. <br />
             O processo chama automaticamente: <br />
             <p>    splitInWords;</p>
             <p>    splitInLines;</p>
             A altura define quantas linhas poderão aparecer por tela, sendo calculado a (linha + espaçamento entre linhas)/tamanho informado
             \param size Define a altura e a largura do texto que será exibido.
            */
            virtual void splitInScreens(Vector2i size);
			
            //! Define internamente o texto.
            /*! Somente define internamente o texto que será exibido. <br />
                Ainda é necessario chamar o metodo para dividir o texto em telas.
             \param text Define a variável text da classe.
             */
			virtual void setText(string text);
            
            //! Define internamente a fonte.
            /*! Define a nova fonte que será carregada, carregando a mesma.
             \param path Fonte a ser carregada
             \return Retorna se foi possivel carregar a fonte ou não, caso já exista uma fonte carregada e o retorno seja (false) a fonte antiga permanece carregada.
             */
			virtual bool setFont(string path);
            
            //! Define a escala da fonte.
            /*! Define a escala da fonte e altera a escala da mesma, desta forma todas as proximas chamadas para definir o tamanho do texto ja levarão em consideração o tamanho novo da fonte.
                A escala será definida tanto para altura como largura
             \param scale Nova escala da fonte
             */
            virtual void setScale(float scale);
            
            //! Define a escala da fonte.
            /*! Define a escala da fonte e altera a escala da mesma, desta forma todas as proximas chamadas para definir o tamanho do texto ja levarão em consideração o tamanho novo da fonte.
             \param scale Nova escala da fonte, scale.x define a largura e scale.y define a altura
             */
            virtual void setScale(Vector2f scale);
            
            //! Define espaçamento entre linhas.
            /*! Define o espaçamento entre as linhas que serão renderizadas na tela. <br />
                O espaçamento é levado em consideração quando o texto é quebrado em linhas.
             \param
             \return
             */
            virtual void setSpacing(int spacing);
            
            //! Define a cor da fonte.
            /*! Define a nova cor assim como transparência da fonte, sendo cada valor entre (0-255).
             \param r Define intensidade do canal vermelho
             \param g Define intensidade do canal verde
             \param b Define intensidade do canal azul
             \param a Define transparencia da fonte
             */
            virtual void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
            
            //! Define a cor da fonte.
            /*! Define a nova cor assim como a transparência da fonte, sendo cada valor entre (0-255).
             \param color Estrutura que define os valored de r, g, b, a
             \return
             */
            virtual void setColor(Color color);
            
            //! Retorna a escala da fonte.
            /*! Retorna a escala da fonte.
             \return É retornado o valor de scale.x, pois neste método toma-se como base que as duas escalas (altura e largura) são iguais.
             */
            virtual float getScalef();
            
            //! Retorna um vetor contendo as duas escalas da fonte.
            /*! Retorna um vetor contendo as duas escalas da fonte.
             \return Vetor contendo as duas escalas da fonte.
             */
            virtual Vector2f getScale();
            
            //! Renderiza o texto na posição x, y.
            /*! Renderiza o texto na posição x, y. <br />
                O número de linhas do texto foi definido pelo parametro height passado para o método <i>splitInScreens</i>.
             \param x Posição x do texto na tela.
             \param y Posição y do texto na tela.
             \param screen Indice do texto a ser renderizado na tela.
             */
			virtual void renderScreen(int x, int y, int screen);
            
            //! Renderiza o texto na posição position.x, position.y.
            /*! Renderiza o texto na posição position.x, position.y. <br />
             O número de linhas do texto foi definido pelo parametro height passado para o método <i>splitInScreens</i>.
             \param position Posição x e y do texto na tela.
             \param screen Indice do texto a ser renderizado na tela.
             */
            virtual void renderScreen(Point2i position, int screen);
            
            //! Renderiza uma linha de texto na posição x, y especificada.
            /*! Renderiza uma linha de texto na posição x, y especificada.<br />
             Porem não leva em consideração se o texto é maior que a tela
             \param x Posição x do texto na tela
             \param y Posição y do texto na tela
             \param text Texto que se deseja renderizar.
             */
			virtual void renderSimpleText(int x, int y, string text);
            
            //! Renderiza uma linha de texto na posição position.x, position.y especificada.
            /*! Renderiza uma linha de texto na posição position.x, position.y especificada.<br />
                Porem não leva em consideração se o texto é maior que a tela
             \param position Posição x e y do texto na tela
             \param text Texto que se deseja renderizar.
             */
            virtual void renderSimpleText(Point2i position, string text);
            
            //! Retorna o numero de telas geradas pelo <i>splitInScreens</i>.
			virtual int numberOfScreens();
            
            //! Retorna o numero de linhas geradas pelo <i>splitInScreens</i>.
			virtual int numberOfLines();
            
            //! Retorna o numero de palavras geradas pelo <i>splitInScreens</i>.
			virtual int numberOfWords();

            
            //! Retorna a largura total do texto informado.
            virtual int getWidth(string text);
            
            //! Retorna altura do maior caractere dentro do texto.
            /*! Analiza todos os caracteres da string e retorna o tamanho do maior caractere encontrado.
             \param text String a ser analizada.
             \return Tamanho do maior caractere dentro da string.
             */
            virtual int getHeight(string text);

            //! Retorna string contendo o texto definido pelo <i>setText</i>.
			virtual string getText();
			
            //! Inicializa e retorna uma fonte contendo.
            /*! Inicializa uma fonte do caminho informado e retorna o ponteiro.
             \param path Caminho onde se encontra a fonte que deve ser inicializada.
             \return Retorna a fonte inicializada ou nullptr caso não tenha sido possivel inicializar a mesma.
             */
			virtual Font* getFont(string path);
            
            //! Retorna o caminho da fonte.
            virtual string getFontPath();
			
            //! Retorna o vetor de telas gerados pelo <i> splitInScreens</i>.
			virtual vector<pair<int, int>> getScreen();
            
            //! Retorna o vetor de linhas gerados pelo <i> splitInScreens</i>.
			virtual vector<string> getLine();
            
            //! Retorna o vetor de palavras gerados pelo <i> splitInScreens</i>.
			virtual vector<string> getWord();
            
            //! Remove todas as telas definidas.
            /*! Remove todas as telas definidas. <br />
                Porem as linhas e palavras continuam existindo. <br />
                O método <i> splitInScreens </i> remove os textos e linhas.
             */
            virtual void clearScreens();

            //! Define a tela onde deve ocorrer o processo de render do texto.
            static void setWindow(sf::RenderWindow* window);
		};
}

#endif