#ifndef __PADDLE__H__
#define __PADDLE__H__
#include "cocos2d.h"

using namespace cocos2d;

class Paddle: public Sprite
{
public:
    Paddle(){};
    ~Paddle(){};

    virtual bool initWithTexture(Texture2D* pTexture) override;
    virtual void onEnter() override;
    virtual void onExit() override;

    Rect getRect();
    bool containsTouchLocation(CCTouch* touch);
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    static Paddle* paddleWithTexture(Texture2D* pTexture);

};

#endif
