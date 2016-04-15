//
//  enemy.cpp
//  FinalRun
//
//  Base enemy class
//
//  Created by Steven Hurtado on 4/5/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "enemy.h"
#include <iostream>

Enemy::Enemy()
{
    
}

Enemy::Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate)
:AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, spawnPoint.x, spawnPoint.y, timeToUpdate), _direction(RIGHT), _maxHealth(0),_currentHealth(0), _vectorX(spawnPoint.x), _vectorY(spawnPoint.y), _speed(0)
{
    
}

void Enemy::update(int elapsedTime, Player &player)
{
    AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}



//LiuFinal class

LiuFinal::LiuFinal()
{
    
}

//enemy position 224, 80, 32, 16
LiuFinal::LiuFinal(Graphics &graphics, Vector2 spawnPoint) : Enemy(graphics, "ItemImage.png", 224, 80, 32, 16, spawnPoint, 140), _startingX(spawnPoint.x), _startingY(spawnPoint.y), _shouldMoveUp(false)
{
    this->setUpAnimations();
    this->playAnimation("Stag");
}
void LiuFinal::update(int elapsedTime, Player &player)
{
    Enemy::update(elapsedTime, player);
    
    //logic for moving up or down
    this->_y += this-> _shouldMoveUp ? -.15: .15;
    if(this->_y > (this-> _startingY + 10) || this->_y < this->_startingY - 10)
    {
        this->_shouldMoveUp = ! this->_shouldMoveUp;
    }
    
    //formula and logic for chasing player
    _vectorX = player.getX() - this->_x;
    _vectorY = player.getY() - this->_y;
    
    double hypotenuse = sqrt(_vectorX*_vectorX + _vectorY*_vectorY);
    _vectorX /= hypotenuse;
    _vectorY /= hypotenuse;
    
    _speed += elapsedTime * globals::TIME_FACTOR;
    
    this->_x += _vectorX*_speed;
    this->_y += _vectorY*_speed;
    //std::cout<<"speed X: " << _speed<<std::endl;
    //std::cout<<"speed y: " << _speed<<std::endl;
    
}

void LiuFinal::draw(Graphics &graphics)
{
    Enemy::draw(graphics);
}

void LiuFinal::animationDone(std::string currentAnimation)
{
    
}

void LiuFinal::setUpAnimations()
{
    this->addAnimation(1, 7, 48, "Stag", 32, 16, Vector2(0,0));
}

void LiuFinal::touchPlayer(Player *player)
{
    std::cout<<"FINAL HIT PLAYER"<< std::endl;
    player->gainHealth(-1);
}
