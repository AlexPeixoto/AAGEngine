//
//  InputHandler.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 1/22/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "InputControl.h"

using namespace std;
using namespace Core;

map<int, bool> InputControl::heldKeyboardKey, InputControl::releasedKeyboardKey, InputControl::pressedKeyboardKey;
map<int, bool> InputControl::pressedJoystickButton, InputControl::heldJoystickButton, InputControl::releasedJoystickButton;
map<int, bool> InputControl::pressedMouseButton, InputControl::heldMouseButton, InputControl::releasedMouseButton;

map<int, float> InputControl::joystickAxis;

Point2i InputControl::mousePosition;

InputControl::_init InputControl::_initializer;

void InputControl::updateStates(){
    for(int key=Keyboard::Key::A; key<=Keyboard::Key::Pause; key++){
        releasedKeyboardKey.at(key)=(heldKeyboardKey.at(key)&&!Keyboard::isKeyPressed((sf::Keyboard::Key)key));
        heldKeyboardKey.at(key)=(Keyboard::isKeyPressed((sf::Keyboard::Key)key));
        pressedKeyboardKey.at(key)=(!pressedKeyboardKey.at(key)&&Keyboard::isKeyPressed((sf::Keyboard::Key)key));

    }
    if(sf::Joystick::isConnected(0)){
        for(int button=0; button<=Joystick::ButtonCount; button++){
            releasedJoystickButton.at(button)=(heldJoystickButton.at(button)&&!sf::Joystick::isButtonPressed(0, button));
            heldJoystickButton.at(button)=(Joystick::isButtonPressed(0, button));
            pressedJoystickButton.at(button)=(!pressedJoystickButton.at(button)&&Joystick::isButtonPressed(0, button));
        }
        for(int axis=Joystick::Axis::X; axis<=Joystick::Axis::PovY; axis++)
            if(Joystick::hasAxis(0, (Joystick::Axis)axis))
                joystickAxis.at(axis)=Joystick::getAxisPosition(0, (Joystick::Axis)axis);
            else
                joystickAxis.at(axis)=0;
    }
    
    for(int button=Mouse::Button::Left; button<=Mouse::Button::XButton2; button++){
        releasedMouseButton.at(button)=(heldMouseButton.at(button)&&!Mouse::isButtonPressed(((Mouse::Button)button)));
        heldMouseButton.at(button)=(Mouse::isButtonPressed(((Mouse::Button)button)));
        pressedMouseButton.at(button)=(!pressedMouseButton.at(button)&&Mouse::isButtonPressed(((Mouse::Button)button)));
    }
    mousePosition=(Point2i)Mouse::getPosition();
}
bool InputControl::getKeyboardKeyStatus(int key, State state){
    if(state==State::Pressed)
        return pressedKeyboardKey.at(key);
    else if(state==State::Released)
        return releasedKeyboardKey.at(key);
    else
        return heldKeyboardKey.at(key);
}
bool InputControl::getJoystickButtonStatus(int button, State state){
    if(state==State::Pressed)
        return pressedJoystickButton.at(button);
    else if(state==State::Released)
        return releasedJoystickButton.at(button);
    else
        return heldJoystickButton.at(button);
}
float InputControl::getJoystickAxis(int axis){
    return joystickAxis.at(axis);
}
bool InputControl::getMouseButtonStatus(int button, State state){
    if(state==State::Pressed)
        return pressedMouseButton.at(button);
    else if(state==State::Released)
        return releasedMouseButton.at(button);
    else
        return heldMouseButton.at(button);
    
}
Point2i InputControl::getMousePosition(){
    return mousePosition;
}