//
//  exit.h
//  FinalRun
//
//  Created by Steven Hurtado on 4/19/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef exit_h
#define exit_h

#include "animatedsprite.h"
#include "globals.h"
#include "player.h"
#include <string>

class Graphics;
class Player;

class Exit: public AnimatedSprite
{
public:
    Exit();
    Exit(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);
    ~Exit();
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    
    //not truly needed
    void animationDone(std::string currentAnimation);
    void setUpAnimations();
    
    void touchPlayer(Player *player);
};


#endif /* exit_h */
