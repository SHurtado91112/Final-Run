//
//  globals.h
//  FinalRun
//
//  Created by Steven Hurtado on 3/25/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef globals_h
#define globals_h

namespace globals
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 640;
    const float TIME_FACTOR = 0.00001f;
    const float SPRITE_SCALE = 2.0f;
}



namespace sides
{
    enum Side{TOP ,BOTTOM, LEFT, RIGHT, NONE};
    
    inline Side getOppositeSide(Side side)
    {
        return side==TOP ? BOTTOM : side == BOTTOM ? TOP :
        side == LEFT ? RIGHT : side == RIGHT ? LEFT :
        NONE;
    }
}

enum Direction
{
    LEFT, RIGHT, UP, DOWN
};

struct Vector2
{
    int x, y;
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y){} 
    Vector2 zero(){ return Vector2(0,0);}
    
};

#endif /* globals_h */
