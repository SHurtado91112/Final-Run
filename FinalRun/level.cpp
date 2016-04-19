//
//  level.cpp
//  FinalRun
//
//  Created by Steven Hurtado on 3/26/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#include "level.h"
#include "graphics.h"
#include "globals.h"

#include "tinyxml2.h"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "notes.h"
#include "exit.h"

using namespace tinyxml2;

Level::Level()
{
    
}

Level::Level(std::string mapName, Graphics &graphics) :
    _mapName(mapName), _size(Vector2(0,0))
{
    this->loadMap(mapName, graphics);
}

Level::~Level()
{
    
}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
    //Parse TMX (XML) file and loads map into graphics
    
    XMLDocument doc;
    std::stringstream ss;
    
    ss << mapName << ".tmx"; //pass in name
    
    doc.LoadFile(ss.str().c_str());
    
    XMLElement * mapNode = doc.FirstChildElement("map");
    
    //get width/height of map, store into size
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width,height);
    
    //get width/height of tile, store into tilesize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth,tileHeight);
    
    //load tilesets
    XMLElement * pTileset = mapNode-> FirstChildElement("tileset");
    if(pTileset != NULL)
    {
        while(pTileset)
        {
            int firstgid;
            const char * source = pTileset -> FirstChildElement("image") -> Attribute("source");
            //char * path;
            std::stringstream ss;
            ss << source;
            
            pTileset -> QueryIntAttribute("firstgid", &firstgid);
            
            SDL_Texture * tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            
            this->_tilesets.push_back(Tileset(tex, firstgid));
            
            pTileset = pTileset -> NextSiblingElement("tileset");
        }
    }

    //loading layers
    XMLElement * pLayer = mapNode -> FirstChildElement("layer");
    if(pLayer != NULL)
    {
        while(pLayer)
        {
            XMLElement * pData = pLayer -> FirstChildElement("data");
            if(pData != NULL)
            {
                while(pData)
                {
                    //loading tile
                    XMLElement * pTile = pData -> FirstChildElement("tile");
                    
                    if(pTile != NULL)
                    {
                        int tileCounter = 0;
                        
                        while(pTile)
                        {
                            //build each tile
                            //none will be built if gid = 0
                            if(pTile -> IntAttribute("gid") == 0)
                            {
                                tileCounter++;
                                if(pTile -> NextSiblingElement("tile"))
                                {
                                    pTile = pTile -> NextSiblingElement("tile");
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            
                            //get tileset for specific gid
                            
                            int gid = pTile -> IntAttribute("gid");
                            Tileset tls;
                            for(int i = 0; i < this-> _tilesets.size(); i++)
                            {
                                if(this->_tilesets[i].FirstGid <= gid)
                                {
                                    //desired tileset
                                    tls = this->_tilesets.at(i);
                                    break;
                                }
                            }
                            
                            //default constructor gives us a negative 1 value
                            if(tls.FirstGid == -1)
                            {
                                //no tileset found
                                tileCounter++;
                                if(pTile -> NextSiblingElement("tile"))
                                {
                                    pTile = pTile -> NextSiblingElement("tile");
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                                
                            }
                            
                            //get position of tile in level
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            // calc position of tile in tileset
                            int tsxx = gid % (tilesetWidth/tileWidth) - 1;
                            tsxx *= tileWidth;
                            
                            int tsyy = 0;
                            int amt = (gid / (tilesetWidth/tileWidth));
                            tsyy = tileHeight * amt;
                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
                            
                            //build actual tile
                            
                            Tile tile(tls.Texture, Vector2(tileWidth,tileHeight), finalTilesetPosition, finalTilePosition);
                            this->_tileList.push_back(tile);
                            tileCounter++;
                            
                            pTile = pTile -> NextSiblingElement("tile");
                        }
                        
                    }
                    pData = pData -> NextSiblingElement("data");
                }
            }
            //loading data element
            pLayer = pLayer -> NextSiblingElement("layer");
        }
    }
    
    //parse the collisions
    XMLElement * pObjectGroup = mapNode -> FirstChildElement("objectgroup");
    if(pObjectGroup != NULL)
    {
        while(pObjectGroup)
        {
            const char * name = pObjectGroup -> Attribute("name");
            std::stringstream ss;
            ss << name;
            
            if(ss.str() == "collisions")
            {
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        float x, y, width, height;
                        x = pObject -> FloatAttribute("x");
                        y = pObject -> FloatAttribute("y");
                        width = pObject -> FloatAttribute("width");
                        height = pObject -> FloatAttribute("height");
                        
                        this->_collisionRects.push_back(Rectangle(
                                                                  std::ceil(x) * globals::SPRITE_SCALE,
                                                                  std::ceil(y) * globals::SPRITE_SCALE,
                                                                  std::ceil(width) * globals::SPRITE_SCALE,
                                                                  std::ceil(height) * globals::SPRITE_SCALE
                                                        ));
                        
                        pObject = pObject -> NextSiblingElement("object");
                    }
                    
                    
                }
            }
            
            else if(ss.str() == "slopes")
            {
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        std::vector<Vector2> points;
                        Vector2 p1;
                        p1 = Vector2(std::ceil(pObject -> FloatAttribute("x")), std::ceil(pObject -> FloatAttribute("y")));
                        
                        XMLElement * pPolyline = pObject -> FirstChildElement("polyline");
                        
                        if(pPolyline != NULL)
                        {
                            std::vector<std::string> pairs;
                            const char * pointString = pPolyline -> Attribute("points");
                            std::stringstream ss;
                            ss<< pointString;
                            Utils::split(ss.str(), pairs, ' ');
                            //loop through pairs, split into vector2 and then store them in point vector
                            
                            for(int i = 0; i < pairs.size(); i++)
                            {
                                std::vector<std::string> ps;
                                Utils::split(pairs.at(i), ps, ',');
                                points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
                            }
                        }
                        
                        for(int i = 0; i < points.size(); i += 2)
                        {
                            this->_slopes.push_back(Slope(
                                                          Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
                                                                  (p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
                                                          Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
                                                                  (p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)));
                        }
                        
                        pObject = pObject -> NextSiblingElement("object");
                    }
                }
            }
            
            //other object groups, else if ss.str() == "others"
            else if(ss.str() == "spawn points")
            {
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        float x = pObject -> FloatAttribute("x");
                        float y = pObject -> FloatAttribute("y");
                        const char * name = pObject -> Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "player")
                        {
                            this->_spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y));
                        }
                        pObject = pObject -> NextSiblingElement("object");
                    }
                }
            }
            
            //parsing for enemy spawn points
            
            else if(ss.str() == "enemies")
            {
                float x,y;
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        x = pObject -> FloatAttribute("x");
                        y = pObject -> FloatAttribute("y");
                        const char * name = pObject -> Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "LiuFinal")
                        {
                            this->_enemies.push_back(new LiuFinal(graphics, Vector2(std::floor(x) * globals::SPRITE_SCALE, std::floor(y))));
                        }
                        pObject = pObject -> NextSiblingElement("object");
                    }
                }
            }

            else if(ss.str() == "Items")
            {
                float x,y;
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        x = pObject -> FloatAttribute("x");
                        y = pObject -> FloatAttribute("y");
                        const char * name = pObject -> Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "Notes")
                        {
                            //Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate //64, 48, 32, 16,
                            this->_notes.push_back(new Notes(graphics, "ItemImage.png", 64, 48, 32, 16, Vector2(std::floor(x) * globals::SPRITE_SCALE, std::floor(y) * globals::SPRITE_SCALE), 100));
                        }
                        pObject = pObject -> NextSiblingElement("object");
                    }
                }
            }
            
            else if(ss.str() == "Exit")
            {
                float x,y;
                XMLElement * pObject = pObjectGroup -> FirstChildElement("object");
                if(pObject != NULL)
                {
                    while(pObject)
                    {
                        x = pObject -> FloatAttribute("x");
                        y = pObject -> FloatAttribute("y");
                        const char * name = pObject -> Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "exit")
                        {
                            //Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate //64, 48, 32, 16,
                            this->_exit.push_back(new Exit(graphics, "ItemImage.png", 64, 48, 32, 16, Vector2(std::floor(x) * globals::SPRITE_SCALE, std::floor(y) * globals::SPRITE_SCALE), 100));
                        }
                        pObject = pObject -> NextSiblingElement("object");
                    }
                }
            }
            
            pObjectGroup = pObjectGroup -> NextSiblingElement("objectgroup");
        }
    
    }

}

void Level::update(int elapsedTime, Player &player)
{
    for(int i = 0; i < this->_enemies.size(); i++)
    {
        this-> _enemies.at(i)->update(elapsedTime, player);
    }
    for(int i = 0; i < this->_notes.size(); i++)
    {
        this->_notes.at(i)->update(elapsedTime);
    }
}

void Level::draw(Graphics &graphics, Player &player)
{
    for(int i = 0; i < this-> _tileList.size(); i++)
    {
        this->_tileList.at(i).draw(graphics, player);
    }
    
    for(int i = 0; i < this-> _enemies.size(); i++)
    {
        this->_enemies.at(i)-> draw(graphics);
    }
    for(int i = 0; i < this-> _notes.size(); i++)
    {
        this->_notes.at(i)-> draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other)
{
    std::vector<Rectangle> others;
    
    for(int i = 0; i < this->_collisionRects.size(); i++)
    {
        if(this->_collisionRects.at(i).collidesWith(other))
        {
            others.push_back(this->_collisionRects.at(i));
        }
    }
    return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other)
{
    std::vector<Slope> others;
    
    for(int i = 0; i < this->_slopes.size(); i++)
    {
        if(this->_slopes.at(i).collidesWith(other))
        {
            others.push_back(this->_slopes.at(i));
        }
    }
    return others;
}

std::vector<Enemy *> Level::checkEnemyCollisions(const Rectangle &other)
{
    std::vector<Enemy*> others;
    for(int i = 0; i < this->_enemies.size(); i++)
    {
        if(this->_enemies.at(i) -> getBoundingBox().collidesWith(other))
        {
            others.push_back(this->_enemies.at(i));
        }
    }
    return others;
}
std::vector<Notes *> Level::checkNotesCollisions(const Rectangle &other)
{
    std::vector<Notes*> others;
    for(int i = 0; i < this->_notes.size(); i++)
    {
        if(this->_notes.at(i) -> getBoundingBox().collidesWith(other))
        {
            others.push_back(this->_notes.at(i));
        }
    }
    return others;
}

std::vector<Exit *> Level::checkExitCollisions(const Rectangle &other)
{
    std::vector<Exit*> others;
    for(int i = 0; i < this->_exit.size(); i++)
    {
        if(this->_exit.at(i) -> getBoundingBox().collidesWith(other))
        {
            others.push_back(this->_exit.at(i));
        }
    }
    return others;
}

const Vector2 Level::getPlayerSpawnPoint() const
{
    return this-> _spawnPoint;
}




