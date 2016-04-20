//
//  item.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 4/12/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//


#ifndef notes_h
#define notes_h
#include "animatedsprite.h"
#include "globals.h"
#include "player.h"
#include <string>

class Graphics;
class Player;

class Notes: public AnimatedSprite
{
public:
    Notes();
    Notes(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);
    ~Notes();
    void update(float elapsedTime);
    void draw(Graphics &graphics);    
    //not truly needed
    void animationDone(std::string currentAnimation);
    void setUpAnimations();
    
    void touchPlayer(Player *player);
};

#endif /* notes_h */
