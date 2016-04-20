//
//  exit.cpp
//  FinalRun
//
//  Class that monitors exit door for game once the player has been reached
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 4/19/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include <stdio.h>
#include "exit.h"
#include "graphics.h"
#include <iostream>

Exit::Exit()
{
    
}

Exit::Exit(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate):AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate)
{
    // graphics.loadImage("ItemImage.png");
    this-> setUpAnimations();
    this-> playAnimation("Item");
}

void Exit::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
}

void Exit::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}


void Exit::animationDone(std::string currentAnimation)
{
    
}

void Exit::setUpAnimations()
{
    this->addAnimation(1, 2, 48, "Item", 32, 16, Vector2(0,0));
}

void Exit::touchPlayer(Player *player)
{
    std::cout<<"Exit HIT PLAYER"<< std::endl;
    player->gameExited();
}

Exit::~Exit()
{

}
