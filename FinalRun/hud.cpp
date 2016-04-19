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
#include <iostream>
//#include "globals.h"

class Notes;

HUD::HUD()
{
    
}

HUD::HUD(Graphics &graphics, Player &player)
{
    this->_player = player;
    this->_noteHolder1 = Sprite(graphics, "ItemImage.png", 96, 48, 32, 16, 1045, 0);
    this->_noteHolder2 = Sprite(graphics, "ItemImage.png", 96, 48, 32, 16, 1085, 0);
    this->_noteHolder3 = Sprite(graphics, "ItemImage.png", 96, 48, 32, 16, 1125, 0);
    this->_noteHolder4 = Sprite(graphics, "ItemImage.png", 96, 48, 32, 16, 1165, 0);
    this->_noteHolder5 = Sprite(graphics, "ItemImage.png", 96, 48, 32, 16, 1205, 0);
    
    this->_noteSprite1 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 1045, 0);
    this->_noteSprite2 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 1085, 0);
    this->_noteSprite3 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 1125, 0);
    this->_noteSprite4 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 1165, 0);
    this->_noteSprite5 = Sprite(graphics, "ItemImage.png", 64, 48, 32, 16, 1205, 0);
    
    this->_grader = Sprite(graphics, "Grader.png", 0, 0, 400, 312, 500, 0);
    
    this->_gradeA = Sprite(graphics, "gradeA.png", 0, 0, 57, 71, 1000, 165);
    this->_gradeB = Sprite(graphics, "gradeB.png", 0, 0, 44, 64, 1000, 165);
    this->_gradeC = Sprite(graphics, "gradeC.png", 0, 0, 45, 72, 1000, 165);
    this->_gradeD = Sprite(graphics, "gradeD.png", 0, 0, 57, 68, 1000, 165);
    this->_gradeF = Sprite(graphics, "gradeF.png", 0, 0, 52, 67, 1000, 165);
}

void HUD::update(int elapsedTime, Player &player)
{
    this->_player = player;
}

void HUD::draw(Graphics &graphics)
{
    this->_noteHolder1.draw(graphics, this->_noteHolder1.getX(), this->_noteHolder1.getY());
    this->_noteHolder2.draw(graphics, this->_noteHolder2.getX(), this->_noteHolder2.getY());
    this->_noteHolder3.draw(graphics, this->_noteHolder3.getX(), this->_noteHolder3.getY());
    this->_noteHolder4.draw(graphics, this->_noteHolder4.getX(), this->_noteHolder4.getY());
    this->_noteHolder5.draw(graphics, this->_noteHolder5.getX(), this->_noteHolder5.getY());
    
    switch(_player.getNotes())
    {
        case 0:
            
            break;
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
        default:
            this->_noteSprite1.draw(graphics, this->_noteSprite1.getX(), this->_noteSprite1.getY());
            this->_noteSprite2.draw(graphics, this->_noteSprite2.getX(), this->_noteSprite2.getY());
            this->_noteSprite3.draw(graphics, this->_noteSprite3.getX(), this->_noteSprite3.getY());
            this->_noteSprite4.draw(graphics, this->_noteSprite4.getX(), this->_noteSprite4.getY());
            this->_noteSprite5.draw(graphics, this->_noteSprite5.getX(), this->_noteSprite5.getY());
            break;

    }
    
    if(_player.getGameEnded())
    {
        switch(_player.getGrade())
        {
            case 0:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
                
                    this->_gradeF.draw(graphics, this->_gradeF.getX(), this->_gradeF.getY());
                
                break;
            case 1:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
                
                this->_gradeF.draw(graphics, this->_gradeF.getX(), this->_gradeF.getY());
                
                break;
            case 2:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
            
                this->_gradeD.draw(graphics, this->_gradeD.getX(), this->_gradeD.getY());
            
                break;
            case 3:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
            
                this->_gradeC.draw(graphics, this->_gradeC.getX(), this->_gradeC.getY());
            
                break;
            case 4:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
            
                this->_gradeB.draw(graphics, this->_gradeB.getX(), this->_gradeB.getY());
            
                break;
            case 5:
                this->_grader.draw(graphics, this->_grader.getX(), this->_grader.getY());
            
                this->_gradeA.draw(graphics, this->_gradeA.getX(), this->_gradeA.getY());
            
                break;
        }
    }
}