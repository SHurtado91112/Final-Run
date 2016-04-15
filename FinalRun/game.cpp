//
//  game.cpp
//  FinalRun
//
//  Information for main game loop
//
//  Created by Steven Hurtado on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include <SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
    
}
Game::~Game()
{
    
}

void Game::gameLoop()
{
    Graphics graphics;
    Input input;
    SDL_Event event;
    
    this-> _level = Level("Map 1", Vector2(100, 100), graphics);
    this-> _player = Player(graphics, this->_level.getPlayerSpawnPoint());
    this-> _hud = HUD(graphics, _player);
    int LAST_UPDATE_TIME = SDL_GetTicks();
    
    
    //game loop starts
    while(true)
    {
        input.beginNewFrame();
        
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                    if(event.key.repeat == 0)
                    {
                        input.keyDownEvent(event);
                    }
            }
            else if(event.type == SDL_KEYUP)
            {
                if(event.key.repeat == 0)
                {
                    input.keyUpEvent(event);
                }
            }
            
            else if(event.type == SDL_QUIT)
            {
                return;
            }
        }
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
        {
            //WILL BE USED TO OUTPUT PAUSE MENU SCREEN (FOR QUITTING AND INVENTORY)
            return;
        }
        else if(input.isKeyHeld(SDL_SCANCODE_LEFT) == true)
        {
            this->_player.moveLeft();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_RIGHT) == true)
        {
            this->_player.moveRight();
        }
        
        if(input.wasKeyPressed(SDL_SCANCODE_UP) == true)
        {
            this->_player.jump();
        }
        
        if(!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
        {
            this->_player.stopMoving();
        }
        
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS =  CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this -> update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();
    this->_level.draw(graphics, this->_player);
    
    this-> _player.draw(graphics);
    
    this-> _hud.draw(graphics);
    
    graphics.flip();
}

void Game::update(float elapsedTime)
{
    this->_player.update(elapsedTime);
    this-> _level.update(elapsedTime, this->_player);
    this-> _hud.update(elapsedTime, this->_player);
    
    
    //check collisions
    std::vector<Rectangle> others;
    if((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        //player collided with at least one tile, and handled
        this->_player.handleTileCollisions(others);
    }
    
    //check slopes
    std::vector<Slope> otherSlopes;
    if((otherSlopes = this->_level.checkSlopeCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleSlopeCollisions(otherSlopes);
    }
    
    //check enemies
    std::vector<Enemy*> otherEnemies;
    if((otherEnemies = this->_level.checkEnemyCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleEnemyCollisions(otherEnemies);
    }
    
    //check notes
    std::vector<Notes*> otherNotes;
    if((otherNotes = this->_level.checkNotesCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleNotesCollisions(otherNotes);
    }
}