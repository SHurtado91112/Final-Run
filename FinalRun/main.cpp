//
//  main.cpp
//  FinalRun
//
//  COP3503 Group Project
//
//  Main of program
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "game.h"
#include <SFML/Audio.hpp>

int main(int argc, const char * argv[])
{
    
    //start of program, using resource from SFML framework to play wav file
    //gator theme
    sf::Music music;
   
    if(!music.openFromFile("GatorChompGoGators.wav"))
    {
        return -1; // error
    }
    music.play();
    
    //create an instance of a game class
    Game game;
    
    //keeps the game going infinitely, until stopped by exit call
    while(true)
    {
        
    }
    
    return 0;
}
