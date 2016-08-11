//
//  InputHandler.h
//  AAGEngine
//
//  Created by Alex Peixoto on 1/22/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__InputHandler__
#define __Action_Adventure_Game_Engine__InputHandler__

#include <iostream>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Point.h"
using std::map;
using std::string;
using std::pair;
using sf::Point2i;
using sf::Keyboard;
using sf::Joystick;
using sf::Mouse;
using std::make_pair;

//IF IS PRESSED AND IN THE LOOP IS PRESSED, CHANGE STATUS IN LOOP TO HELD
namespace Core{
class InputControl{
public:
    
    //! Define estados das teclas
    enum State{
        Pressed, /*!< Pressionada. */
        Held, /*!< Pressionada desde o ultimo frame. */
        Released /*!< Solta. */
    };
    // Redefine know types
    //! Define o tipo para teclas do teclado.
    typedef Keyboard::Key KeyboardKey;
    //! Define o tipo para botões do mouse.
    typedef Mouse::Button MouseButton;
    //! Define o tipo para eixos do joystick.
    typedef Joystick::Axis JoystickAxis;

    
private:
    //! Mapeia teclas pressionadas do teclado que no ultimo updateStates não se encontravam pressionada.
    static map<int, bool> pressedKeyboardKey;
    //! Mapeia teclas pressionadas do teclado que no ultimo updateStates se encontravam pressionada.
    static map<int, bool>  heldKeyboardKey;
    //! Mapeia teclas soltas do teclado que no ultimo updateStates se encontravam pressionada.
    static map<int, bool>  releasedKeyboardKey;
    
    //! Mapeia teclas pressionadas do joystick que no ultimo updateStates não se encontravam pressionada.
    static map<int, bool> pressedJoystickButton;
    //! Mapeia teclas pressionadas do joystick que no ultimo updateStates se encontravam pressionada.
    static map<int, bool> heldJoystickButton;
    //! Mapeia teclas soltas do joystick que no ultimo updateStates se encontravam pressionada.
    static map<int, bool> releasedJoystickButton;
    
    //! Mapeia cada eixo do joystick e seu movimento.
    static map<int, float> joystickAxis;
    
    //! Mapeia botões pressionados do mouse que no ultimo updateStates não se encontravam pressionados.
    static map<int, bool> pressedMouseButton;
    //! Mapeia botões pressionados do mouse que no ultimo updateStates se encontravam pressionados.
    static map<int, bool> heldMouseButton;
    //! Mapeia botões pressionados do mouse que no ultimo updateStates se encontravam pressionados.
    static map<int, bool> releasedMouseButton;
    //! Define a posição do mouse.
    static Point2i mousePosition;

    //! Initialize all states on the static class
    static class _init{
    public:
        _init(){
            for(int key=Keyboard::Key::A; key<=Keyboard::Key::Pause; key++){
                pressedKeyboardKey.insert(make_pair(key, false));
                heldKeyboardKey.insert(make_pair(key, false));
                releasedKeyboardKey.insert(make_pair(key, false));
            }
            for(int button=0; button<=Joystick::ButtonCount; button++){
                pressedJoystickButton.insert(make_pair(button, false));
                heldJoystickButton.insert(make_pair(button, false));
                releasedJoystickButton.insert(make_pair(button, false));
            }
            for(int button=Mouse::Button::Left; button<=Mouse::Button::XButton2; button++){
                pressedMouseButton.insert(make_pair(button, false));
                heldMouseButton.insert(make_pair(button, false));
                releasedMouseButton.insert(make_pair(button, false));
            }
            for(int axis=Joystick::Axis::X; axis<=Joystick::Axis::PovY; axis++)
                joystickAxis.insert(make_pair(axis, false));
        }
    } _initializer;
public:
    //! Atualiza estados do joystick, mouse e teclado.
    static void updateStates();
    
    //! Verifica se a tecla do teclado se encontra no estado informado.
    /*!
     \param key Código da tecla do teclado.
     \param state Estado que se deseja verificar.
     \return Retorna se a tecla se encontra no estado informado.
     */
    static bool getKeyboardKeyStatus(int key, State state);
    //! Verifica se a tecla do joystick se encontra no estado informado.
    /*!
     \param button Código da tecla do joystick.
     \param state Estado que se deseja verificar.
     \return Retorna se a tecla se encontra no estado informado.
     */
    static bool getJoystickButtonStatus(int button, State state);
    //! Retorna o valor do eixo do joystick.
    static float getJoystickAxis(int axis);
    //! Verifica se o botão do mouse se encontra no estado informado.
    /*!
     \param button Código do botão do mouse.
     \param state Estado que se deseja verificar.
     \return Retorna se o botão se encontra no estado informado.
     */
    static bool getMouseButtonStatus(int button, State state);
    //! Retorna a posição do mouse.
    static Point2i getMousePosition();
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__InputHandler__) */
