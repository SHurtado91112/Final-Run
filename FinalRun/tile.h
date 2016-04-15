//
//  tile.h
//  FinalRun
//
//  Created by Steven Hurtado on 3/27/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef tile_h
#define tile_h
#include "globals.h"
#include "player.h"

class SDL_Texture;
class Graphics;

class Tile
{
private:
    SDL_Texture * _tileset;
    Vector2 _size;
    Vector2 _tilesetPosition;
    Vector2 _position;
    
public:
    Tile();
    Tile(SDL_Texture * tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
    void update(int elapsedTime);
    void draw(Graphics &graphics, Player &player);
};
#endif /* tile_h */
