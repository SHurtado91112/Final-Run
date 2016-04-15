//
//  animatedsprite.h
//  FinalRun
//
//  Created by Steven Hurtado on 3/25/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef animatedsprite_h
#define animatedsprite_h

#include <map>
#include <string>
#include "sprite.h"
#include "globals.h"
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite
{
private:
    std::map<std::string, std::vector<SDL_Rect> > _animations;
    std::map<std::string, Vector2> _offsets;

    int _frameIndex;
    double _timeElapsed;
    bool _visible;
    
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);
    //~AnimatedSprite();
    
    //plays animation assuming it is not playing already
    void playAnimation(std::string animation, bool once = false);
    
    void update(int elapsedTime);
    
    void draw(Graphics &graphics, int x, int y);
    
    
protected:
    double _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;
    
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
    
    void resetAnimation();
    
    void stopAnimation();
    
    void setVisible(bool visible);
    const inline bool getVisible() const{return _visible;}
    virtual void animationDone(std::string currentAnimation) = 0;
    
    virtual void setUpAnimations() = 0;
};

#endif /* animatedsprite_h */
