//
//  level.h
//  FinalRun
//
//  Created by Steven Hurtado on 3/26/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef level_h
#define level_h
#include "globals.h"
#include <string>
#include "tile.h"
#include <vector> 
#include "rectangle.h"
#include "slope.h"

class Graphics;
class Player;
class Enemy;
class Notes;
class Exit;
class Tile;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level
{
private:
    std::string _mapName;
    Vector2 _spawnPoint;
    
    Vector2 _size;
    Vector2 _tileSize;
    
    
    SDL_Texture * _backgroundTexture;
    
    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    std::vector<Rectangle> _collisionRects;
    std::vector<Slope> _slopes;
    std::vector<Enemy*> _enemies;
    std::vector<Notes*> _notes;
    std::vector<Exit*> _exit;
    
    void loadMap(std::string mapName, Graphics &graphics);
public:
    Level();
    Level(std::string mapName, Graphics &graphics);
    ~Level();
    
    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics, Player &player);
    
    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
    std::vector<Enemy*> checkEnemyCollisions(const Rectangle &other);
    std::vector<Notes*> checkNotesCollisions(const Rectangle &other);
    std::vector<Exit *> checkExitCollisions(const Rectangle &other);
    
    const Vector2 getPlayerSpawnPoint() const;
};

struct Tileset
{
    SDL_Texture * Texture;
    
    int FirstGid;
    
    Tileset()
    {
        this->FirstGid = -1;
    }
    
    Tileset(SDL_Texture * texture, int firstGid)
    {
        this->Texture = texture;
        this->FirstGid = firstGid;
    }
};

#endif /* level_h */
