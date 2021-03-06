//
//  graphics.cpp
//  FinalRun
//
//  Graphics Class will hold all information dealing with graphics
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "globals.h"

Graphics::Graphics()
{
    
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Final Run - COP3503 Group Project");
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface * Graphics::loadImage(const std::string &filePath)
{
    if(this->_spriteSheets.count(filePath) == 0)
    {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture * texture, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle)
{
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer * Graphics::getRenderer() const
{
    return this->_renderer;
}