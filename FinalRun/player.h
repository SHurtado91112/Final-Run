//
//  player.h
//  FinalRun
//
//  Created by Steven Hurtado on 3/26/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef player_h
#define player_h
#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"
#include "enemy.h"
#include "notes.h"

class Graphics;
class Enemy;
class Notes;

class Player : public AnimatedSprite
{
    
private:
    float _dx, _dy;
    
    Direction _facing;
    
    bool _grounded;
    
    int _maxHealth;
    int _currentHealth;
    
    int _notesCollected = 0;
    
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setUpAnimations();
    
    void handleTileCollisions(std::vector<Rectangle> &others);
    void handleSlopeCollisions(std::vector<Slope> &others);
    void handleEnemyCollisions(std::vector<Enemy*> &others);
    void handleNotesCollisions(std::vector<Notes*> &others);
    
    const float getX() const;
    const float getY() const;
    
    const inline float getdX() const {return this->_dx;}
    const inline float getdY() const {return this-> _dy;}
    
    const inline int getMaxHealth() const{return this->_maxHealth;}
    const inline int getCurrentHealth() const{return this->_currentHealth;}
    
    void gainHealth(int amount);
    
    bool _timerBool = true;
    
    void incrNotes();
    
    inline int getNotes() const {return this->_notesCollected;}
    
};
#endif /* player_h */
