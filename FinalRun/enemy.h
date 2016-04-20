//
//  enemy.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 4/5/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef enemy_h
#define enemy_h
#include "animatedsprite.h"
#include "globals.h"
#include "player.h"
#include <string>
class Graphics;
class Player;

class Enemy : public AnimatedSprite
{
public:
    Enemy();
    Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);
    virtual void update(int elapsedTime, Player &player);
    virtual void draw(Graphics &graphics);
    virtual void touchPlayer(Player *player) = 0;
    const inline int getMaxHealth() const { return this-> _maxHealth;}
    const inline int getCurrentHealth() const { return this-> _currentHealth;}
protected:
    Direction _direction;
    int _maxHealth;
    int _currentHealth;
    double _vectorX;
    double _vectorY;
    double _speed;
};

class LiuFinal : public Enemy
{
private:
    float _startingX, _startingY;
    bool _shouldMoveUp;
public:
    LiuFinal();
    LiuFinal(Graphics &graphics, Vector2 spawnPoint);
    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
    void touchPlayer(Player *player);
    //not needed for this enemy
    void animationDone(std::string currentAnimation);
    void setUpAnimations();
};
#endif /* enemy_h */
