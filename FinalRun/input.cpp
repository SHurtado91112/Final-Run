//
//  input.cpp
//  FinalRun
//
//  class for keeping track of user input
//
//  Created by Steven Hurtado on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "input.h"

//gets called at the beginning of every new frame
//resets irrelevant keys
void Input::beginNewFrame()
{
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
    
}

//called when key pressed
void Input::keyDownEvent(const SDL_Event &event)
{
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}


//called when key released
void Input::keyUpEvent(const SDL_Event &event)
{
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

//check if key was pressed during frame call
bool Input::wasKeyPressed(SDL_Scancode key)
{
    return this->_pressedKeys[key];
}

//check if key was released during frame call
bool Input::wasKeyReleased(SDL_Scancode key)
{
    return this->_releasedKeys[key];
}

//check if key is currently being held during frame call
bool Input::isKeyHeld(SDL_Scancode key)
{
    return this->_heldKeys[key];
}