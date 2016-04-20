//
//  player.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/26/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef player_h
#define player_h
#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"
#include "enemy.h"
#include "notes.h"
#include "level.h"
#include "exit.h"

class Graphics;
class Enemy;
class Notes;
class Exit;
class Level;

class Player : public AnimatedSprite
{
    
private:
    float _dx, _dy;
    
    Direction _facing;
    
    bool _grounded;
    
    int _maxHealth;
    int _currentHealth;
    
    int _notesCollected = 0;
    int _grade = 0;
    bool _gameEnded = false;
    bool _gameExited = false;
    
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    void down();
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setUpAnimations();
    
    void handleTileCollisions(std::vector<Rectangle> &others);
    void handleSlopeCollisions(std::vector<Slope> &others);
    void handleEnemyCollisions(std::vector<Enemy*> &others, Level &level, Graphics &graphics);
    void handleNotesCollisions(std::vector<Notes*> &others);
    void handleExitCollisions(std::vector<Exit*> &others);
    
    const float getX() const;
    const float getY() const;
    
    const inline float getdX() const {return this->_dx;}
    const inline float getdY() const {return this-> _dy;}
    
    const inline int getMaxHealth() const{return this->_maxHealth;}
    const inline int getCurrentHealth() const{return this->_currentHealth;}
    inline int getGrade() {return _grade;}
    inline bool getGameEnded() {return _gameEnded;}
    inline bool getGameExit() {return _gameExited;}
    
    void gainHealth(int amount);
    
    bool _timerBool = true;
    
    void incrNotes();
    
    inline int getNotes() const {return this->_notesCollected;}
    
    void setGravity(int g);
    inline void setGrade(int g) {_grade = g;}
    inline void gameEnded() { _gameEnded = true;}
    inline void gameExited() {_gameExited = true;}
};
#endif /* player_h */
