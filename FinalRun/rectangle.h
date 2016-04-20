//
//  rectangle.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 3/27/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef rectangle_h
#define rectangle_h
#include "globals.h"

class Rectangle
{
private:
    int _x, _y, _width, _height;
public:
    
    Rectangle()
    {
        
    }
    
    Rectangle(int x, int y, int width, int height) :
        _x(x), _y(y), _width(width), _height(height)
    {
        
    }
    
    const int getCenterX() const {return this->_x + this->_width/2;}
    const int getCenterY() const {return this->_y + this->_height/2;}
    
    const int getLeft() const {return this->_x;}
    const int getRight() const {return this->_x + this->_width;}
    const int getTop() const {return this->_y;}
    const int getBottom() const {return this->_y + this->_height;}
    
    const int getWidth() const {return this->_width;}
    const int getHeight() const {return this->_height;}
    
    const int getSide(const sides::Side side) const
    {
        return side == sides::LEFT ? this->getLeft() :
        side == sides::RIGHT ? this->getRight() :
        side == sides::TOP ? getTop() :
        side == sides::BOTTOM ? getBottom() :
        sides::NONE;
    }
    //takes another rectangle and checks bounds for collision
    const bool collidesWith(const Rectangle &other) const
    {
        return
            this->getRight() >= other.getLeft() &&
            this->getLeft() <= other.getRight() &&
            this->getTop() <= other.getBottom() &&
            this->getBottom() >= other.getTop();
    }
    
    const bool isValidRectangle() const
    {
        return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
    }
};

#endif /* rectangle_h */
