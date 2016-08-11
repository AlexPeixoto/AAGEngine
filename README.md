Introdution
----------

This is an 2D action adventure game engine. This Engine was developed using C++11 and SFML. The SFML library can be found at: http://www.sfml-dev.org.
This library was tested on Mac OS X (10.9, 10.10 and 10.11).

The SFML used for this project is the 2.1.

How to Generate the library

——————————————

This project was created using XCODE and does not have a CMake or Makefile to compile it.
To generate the library by hand use:
llvm-g++ -g -std=c++11 -dynamiclib -o aagengine.dylib *.cpp  -I./ -I/SFMLPATH/include -L /SFMLPATH/lib -lsfml-graphics.2.1 -lsfml-system.2.1 -lsfml-window.2.1 -lsfml-audio.2.1

To generate the binary use:

llvm-g++ -g -std=c++11 ./*.cpp -L./EngineLibrary - aagengine -I./EngineLibrary  -o game -I/caminhoparaosfml/include  -L /caminhoparaosfml/lib -lsfml-graphics.2.1 -lsfml-system.2.1 -lsfml-window.2.1 -lsfml-audio.2.1

The Example folder provides some code describing how to develop using the Engine.
The Engine folder contains all the Engine files, those are not separated into folders because the original Xcode Project created virtual folders inside the project. The CMake/Makefiles are yet to be written.


Introdução
----------

A biblioteca Action Adventure Game Engine (AAGEngine) é uma biblioteca para desenvolvimento de jogos 2D do gênero aventura. A AAGEngine foi desenvolvida utilizando a linguagem C++11 com a biblioteca SFML. A biblioteca SFML pode ser encontrada em: http://www.sfml-dev.org/ ou no seu projeto do github: https://github.com/SFML/SFML

Dependência da SFML
-------------------

A AAGEngine foi desenvolvida sobre a biblioteca SFML. Esta deve ser baixada no site da própria biblioteca na versão 2.1. A SFML encontra-se disponível para Windows, Linux e Mac OS X. Espera-se que a AAGEngine possa ser compilada em qualquer ambiente onde a SFML e um compilador C++11 estejam disponíveis. Contudo, ela foi testada apenas nos ambientes Windows e Mac OS X.

Estrutura de arquivos
----------------------

Para se ter acesso ao projeto é necessário clonar o código do github clicando em “Clone in desktop” ou utilizando a URL que o próprio github disponibiliza  (https://github.com/AAGEngine/AAGEngine.git).

O projeto é dividido em dois diretórios: Engine e Example. No diretório Engine reside o conteúdo necessário para a compilação da biblioteca, tanto dinamicamente quanto estaticamente. O diretório Example contêm arquivos de exemplo, como a  implementação de diferentes níveis. O mesmo pode ser compilado, porém os assets do exemplo não estão disponíveis no momento por questões de copyright.

Como gerar um binário
----------------------

Para gerar o binário final de um aplicativo são sugeridas duas formas: 

1)    Gerar uma biblioteca estática, ou dinâmica, e colocá-la como dependência, junto com a SFML, do binário gerado.
2)    Compilar o binário com o código da Engine, tendo como única dependência a SFML.

É recomendada a utilização da primeira opção, se possível como biblioteca dinâmica, permitindo a atualização da biblioteca sem a necessidade de se recompilar o binário, caso não ocorram mudanças em assinaturas de métodos.

Para se compilar a biblioteca é necessário referenciar os includes do SFML e as bibliotecas Graphics, System, Window e Audio. É possível é compilar diretamente, utilizando llvm ou g++, assim como a partir de uma IDE. A configuração de ambientes gráficos de compilação é especifico da própria IDE e por isso não é abordado nesse documento.
A seguir é apresentado um exemplo de compilação manual em um ambiente Mac OS X:

Biblioteca:

llvm-g++ -g -std=c++11 -dynamiclib -o aagengine.dylib *.cpp  -I./ -I/caminhoparaosfml/include  -L /caminhoparaosfml/lib -lsfml-graphics.2.1 -lsfml-system.2.1 -lsfml-window.2.1 -lsfml-audio.2.1

Gerando assim uma biblioteca dinâmica, o processo de compilação para o ambiente Linux é semelhante, porem o objeto gerado é do tipo SO (Shared Object).

Binário:

llvm-g++ -g -std=c++11 ./*.cpp -L./EngineLibrary - aagengine -I./EngineLibrary  -o game -I/caminhoparaosfml/include  -L /caminhoparaosfml/lib -lsfml-graphics.2.1 -lsfml-system.2.1 -lsfml-window.2.1 -lsfml-audio.2.1

É importante lembrar que este é somente um exemplo e pode variar entre compiladores, o g++ utiliza configurações semelhantes. Em qualquer ambiente é necessário é referenciar os includes assim como o caminho das bibliotecas.
