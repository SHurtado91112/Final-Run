//
//  game.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef game_h
#define game_h
#include "player.h"
#include "level.h"
#include "hud.h"
#include "graphics.h"

class Game
{
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    Player _player;
    Level _level;
    HUD _hud;
    Graphics _graphics;
public:
    Game();
    ~Game();
    
};


#endif /* game_h */
