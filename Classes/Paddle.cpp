#include "Paddle.h"

bool Paddle::initWithTexture(Texture2D* pTexture)
{
    if (Sprite::initWithTexture(pTexture))
    {
        return true;
    }

    return false;
}

void Paddle::onEnter()
{
    Sprite::onEnter();

    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(Paddle::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Paddle::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Paddle::onTouchEnded, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Paddle::onExit()
{
    Sprite::onExit();
}

Rect Paddle::getRect()
{
    Size size = getTexture()->getContentSize();
    return Rect(-size.width / 2, -size.height / 2, size.width, size.height);
}

bool Paddle::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::onTouchBegan(Touch* touch, Event* event)
{

    if (!containsTouchLocation(touch))
    {
        return false;
    }
    return true;
}

void Paddle::onTouchMoved(Touch* touch, Event* event)
{

}

void Paddle::onTouchEnded(Touch* touch, Event* event)
{

}

Paddle* Paddle::paddleWithTexture(Texture2D* texture)
{

    Paddle *sprite = new Paddle();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

