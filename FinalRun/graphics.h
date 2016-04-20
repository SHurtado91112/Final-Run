//
//  graphics.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <map>
#include <string>
#include <SDL2/SDL.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
  
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    
    std::map<std::string, SDL_Surface*> _spriteSheets;
    
public:
    Graphics();
    ~Graphics();
    
    //loads image into _spritesheetmap if it doesn't already exist
    SDL_Surface * loadImage(const std::string &filePath);
    
    //draws source into certain part of the screen
    void blitSurface(SDL_Texture * source, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle);
    
    //renders everything to screen
    void flip();
    
    //clears screen
    void clear();
    
    SDL_Renderer * getRenderer() const;
};

#endif /* graphics_h */
