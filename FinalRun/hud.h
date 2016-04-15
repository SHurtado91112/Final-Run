//
//  hud.h
//  FinalRun
//
//  Created by Steven Hurtado on 4/5/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef hud_h
#define hud_h
#include "sprite.h"
#include "player.h"

class Graphics;

class HUD
{
private:
    Player _player;
    
    //notes dimensions
    //x = [64][96], y = [48][64], width = 32, height = 16
    Sprite _noteSprite1;
    Sprite _noteSprite2;
    Sprite _noteSprite3;
    Sprite _noteSprite4;
    Sprite _noteSprite5;
    
public:
    HUD();
    HUD(Graphics &graphics, Player &player);
    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
};


#endif /* hud_h */
