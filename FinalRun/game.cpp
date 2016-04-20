//
//  game.cpp
//  FinalRun
//
//  Information for main game loop
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include <SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include <iostream>

namespace
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
    //function from SDL framework that initializes any necessary values
    SDL_Init(SDL_INIT_EVERYTHING);
    
    //enter gameloop
    this->gameLoop();
    
}
Game::~Game()
{
    
}

void Game::gameLoop()
{
    
    //create instance of graphics class, input class, and SDL_Event class
    Graphics graphics;
    Input input;
    SDL_Event event;
    
    //create first level, from map titled "Map 1"
    this-> _level = Level("Map 1", graphics);
    
    //create player instance
    this-> _player = Player(graphics, this->_level.getPlayerSpawnPoint());
    
    //create Heads Up Display instance
    this-> _hud = HUD(graphics, _player);
    
    //retrieve the last update time
    int LAST_UPDATE_TIME = SDL_GetTicks();
    
    
    //game loop starts
    while(true)
    {
        input.beginNewFrame();
        
        //event listening for keys and other possible functions
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
        
        //update the time
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS =  CURRENT_TIME_MS - LAST_UPDATE_TIME;
        
        this->_graphics = graphics;
        
        this -> update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        //draw the updated graphics instance
        this->draw(graphics);
        
        //gets boolean to see if the game has been exited
        if(_player.getGameExit())
        {
            exit(0);//exits the game;
        }
    }
    
}

//function to draw the graphics
void Game::draw(Graphics &graphics)
{
    graphics.clear();
    this->_level.draw(graphics, this->_player);
    
    this-> _player.draw(graphics);
    
    this-> _hud.draw(graphics);
    
    //passes the rendered image
    graphics.flip();
}

//updates several instances
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
    
    //check slopes, not used for this project
    std::vector<Slope> otherSlopes;
    if((otherSlopes = this->_level.checkSlopeCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleSlopeCollisions(otherSlopes);
    }
    
    //check enemies
    std::vector<Enemy*> otherEnemies;
    if((otherEnemies = this->_level.checkEnemyCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleEnemyCollisions(otherEnemies, _level, _graphics);
    }
    
    //check notes
    std::vector<Notes*> otherNotes;
    if((otherNotes = this->_level.checkNotesCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleNotesCollisions(otherNotes);
    }
    
    //check exiting
    std::vector<Exit*> otherExit;
    if((otherExit = this->_level.checkExitCollisions(this->_player.getBoundingBox())).size() > 0)
    {
        this->_player.handleExitCollisions(otherExit);
    }
}