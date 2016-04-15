//
//  sprite.h
//  FinalRun
//
//Holds information for general sprites
//
//  Created by Steven Hurtado on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef sprite_h
#define sprite_h
#include <string>
#include <SDL2/SDL.h>
#include "rectangle.h"
#include "globals.h"
class Graphics;

class Sprite
{
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);
    
    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;
    
    const inline float getX() const {return _x;}
    const inline float getY() const {return _y;}
    
protected:
    SDL_Rect _sourceRect;
    SDL_Texture * _spriteSheet;
    float _x, _y;
    
    Rectangle _boundingBox;
    
private:
    
};


#endif /* sprite_h */
