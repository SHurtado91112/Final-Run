//
//  item.cpp
//  FinalRun
//
//  Class for Notes, item to be picked up
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 4/12/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include <stdio.h>
#include "notes.h"
#include "graphics.h"
#include <iostream>

Notes::Notes()
{
    
}

Notes::Notes(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate):AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate)
{
   // graphics.loadImage("ItemImage.png");
    this-> setUpAnimations();
    this-> playAnimation("Item");
}

void Notes::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
}

void Notes::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}


void Notes::animationDone(std::string currentAnimation)
{
    
}

void Notes::setUpAnimations()
{
    this->addAnimation(1, 2, 48, "Item", 32, 16, Vector2(0,0));
}

void Notes::touchPlayer(Player *player)
{
    std::cout<<"NOTES HIT PLAYER"<< std::endl;
    
    if(this->getVisible())
    {
        player->incrNotes();
        setVisible(false);
    }
    
    std::cout<<"NOTES: "<<player->getNotes()<<std::endl;
    
}

Notes::~Notes()
{
    std::cout<<"NOTESSss DELEteeeteeeee"<<std::endl;
    //player->incrNotes;
}
