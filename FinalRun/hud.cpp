//
//  hud.cpp
//  FinalRun
//
//  Created by Steven Hurtado on 4/5/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "hud.h"
#include "graphics.h"
#include "notes.h"
//#include "globals.h"

class Notes;

HUD::HUD()
{
    
}

HUD::HUD(Graphics &graphics, Player &player)
{
    this->_player = player;
    this->_noteSprite1 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 405, 10);
    this->_noteSprite2 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 445, 10);
    this->_noteSprite3 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 485, 10);
    this->_noteSprite4 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 525, 10);
    this->_noteSprite5 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 565, 10);
}

void HUD::update(int elapsedTime, Player &player)
{
    this->_player = player;
}

void HUD::draw(Graphics &graphics)
{
    switch(_player.getNotes())
    {
        case 1:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            break;
        case 2:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            this->_noteSprite2.draw(graphics, this->_noteSprite2.getX(), this->_noteSprite2.getY());
            break;
        case 3:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            this->_noteSprite2.draw(graphics, this->_noteSprite2.getX(), this->_noteSprite2.getY());
            this->_noteSprite3.draw(graphics, this->_noteSprite3.getX(), this->_noteSprite3.getY());
            break;
        case 4:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            this->_noteSprite2.draw(graphics, this->_noteSprite2.getX(), this->_noteSprite2.getY());
            this->_noteSprite3.draw(graphics, this->_noteSprite3.getX(), this->_noteSprite3.getY());
            this->_noteSprite4.draw(graphics, this->_noteSprite4.getX(), this->_noteSprite4.getY());
            break;
        case 5:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            this->_noteSprite2.draw(graphics, this->_noteSprite2.getX(), this->_noteSprite2.getY());
            this->_noteSprite3.draw(graphics, this->_noteSprite3.getX(), this->_noteSprite3.getY());
            this->_noteSprite4.draw(graphics, this->_noteSprite4.getX(), this->_noteSprite4.getY());
            this->_noteSprite5.draw(graphics, this->_noteSprite5.getX(), this->_noteSprite5.getY());

            break;
        default:
            break;

    }
}