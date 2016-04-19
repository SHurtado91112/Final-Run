//
//  main.cpp
//  FinalRun
//
//  COP3503 Group Project
//
//  Main of program
//
//  Created by Steven Hurtado on 3/24/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "game.h"
#include <SFML/Audio.hpp>

int main(int argc, const char * argv[])
{
    sf::Music music;
   
    if(!music.openFromFile("GatorChompGoGators.wav"))
    {
        return -1; // error
    }
    music.play();
    
    Game game;
    
    while(true)
    {
        
    }
    
    return 0;
}
