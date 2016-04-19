//
//  player.cpp
//  FinalRun
//
//  Created by Steven Hurtado on 3/26/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include <stdio.h>
#include "player.h"
#include "graphics.h"
#include "exit.h"

class Level;

namespace player_constants
{
    const float WALK_SPEED = 0.2f;
    /*const*/ float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const float JUMP_SPEED = 0.7f;
}

Player::Player()
{
    
}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
AnimatedSprite(graphics, "myChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100), _dx(0), _dy(0), _facing(RIGHT), _grounded(false),
    _maxHealth(1), _currentHealth(1)
{
    graphics.loadImage("myChar.png");
    this-> setUpAnimations();
    this-> playAnimation("RunRight");
}


void Player::setUpAnimations()
{
    this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0,0));
    this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0,0));
    this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0,0));
    this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation)
{
    
}

const float Player::getX() const
{
    return this->_x;
}
const float Player::getY() const
{
    return this->_y;
}
void Player::moveLeft()
{
    this -> _dx = -player_constants::WALK_SPEED;
    this -> playAnimation("RunLeft");
    this -> _facing = LEFT;
}

void Player::moveRight()
{
    this -> _dx = player_constants::WALK_SPEED;
    this -> playAnimation("RunRight");
    this -> _facing = RIGHT;
}

void Player::stopMoving()
{
    this -> _dx = 0.0f;
    this -> playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::down()
{
    if(player_constants::GRAVITY == 0)
    {
        this->_dy = 0;
        this->_dy += player_constants::JUMP_SPEED;
        
    }
}

void Player::jump()
{
    if(this->_grounded)
    {
        this->_dy= 0;
        this->_dy -= player_constants::JUMP_SPEED;
        this->_grounded = false;
    }
}

void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
    for(int i = 0; i < others.size(); i++)
    {
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if(collisionSide != sides::NONE)
        {
            switch(collisionSide)
            {
                case sides::TOP:
                    this->_dy = 0;
                    this->_y = others.at(i).getBottom() + 1;
                    if(this->_grounded)
                    {
                        this->_dx = 0;
                        this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
                        
                    }
                    break;
                case sides::BOTTOM:
                    this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
                    this->_dy = 0;
                    this->_grounded = true;
                    break;
                case sides::LEFT:
                    this->_x = others.at(i).getRight() + 1;
                    break;
                case sides::RIGHT:
                    this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
                    break;
            }
        }
        
    }
}

void Player::handleSlopeCollisions(std::vector<Slope> &others)
{
    for(int i = 0; i < others.size(); i++)
    {
        //calculate where on the slope the player's bottom center is colliding
        //y = mx + b to calc slope y position to place player
        
        int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));
        
        int centerX = this->_boundingBox.getCenterX();
        
        int newY = (others.at(i).getSlope() * centerX) + b - 8; //8 = temporary variable to smoothen out slope position
        
        if(this->_grounded)
        {
            this->_y = newY - this->_boundingBox.getHeight();
            this->_grounded = true;
        }
        
    }
}

void Player::handleEnemyCollisions(std::vector<Enemy*> &others, Level &level, Graphics &graphics)
{
    for(int i = 0; i < others.size(); i++)
    {
        level = Level("Map 2", graphics);
        this->_x = level.getPlayerSpawnPoint().x;
        this->_y = level.getPlayerSpawnPoint().y;
        this->setGrade(this->getNotes());
        this->gameEnded();
    }
}

void Player::handleNotesCollisions(std::vector<Notes*> &others)
{
    for(int i = 0; i < others.size(); i++)
    {
        others.at(i)->touchPlayer(this);
    }
}

void Player::handleExitCollisions(std::vector<Exit*> &others)
{
    for(int i = 0; i < others.size(); i++)
    {
        others.at(i)->touchPlayer(this);
    }
}

void Player::incrNotes()
{
    if(this->_timerBool)
    {
        this->_notesCollected++;
    }
}

void Player::setGravity(int g)
{
    player_constants::GRAVITY = g;
}

void Player::gainHealth(int amount)
{
    this->_currentHealth += amount;
}

void Player::update(float elapsedTime)
{
    //apply gravity
    if(this->_dy <= player_constants::GRAVITY_CAP)
    {
        this->_dy += player_constants::GRAVITY * elapsedTime;
    }
    
    //move by dx
    this-> _x += this-> _dx * elapsedTime;
    
    //move by dy
    this->_y += this->_dy * elapsedTime;
    
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this-> _x, this-> _y);
}