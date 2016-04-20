//
//  input.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef input_h
#define input_h
#include <map>
#include <SDL2/SDL.h>

class Input
{
    
private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
    
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event &event);
    void keyDownEvent(const SDL_Event &event);
    
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
    
};

#endif /* input_h */
