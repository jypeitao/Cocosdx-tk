#include "Tank.h"
#include "Bullet.h"

Tank::Tank() :
        mBullet(NULL),
        mTileMapInfo(NULL),
        mBulletDelta(0.0),
        mObjType(PlayerTank),
        IsBlock(false)

{

}

Tank::~Tank()
{

}

Tank* Tank::createTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo)
{
    SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
    pCache->addSpriteFramesWithFile("tank.plist");

    Tank* tank = new Tank();
    tank->initTankWithTankType(tankTypeName, tileMapInfo);
    tank->autorelease();

    return tank;
}

void Tank::initTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo)
{
    initWithSpriteFrameName(tankTypeName);
    mTileMapInfo = tileMapInfo;

    mTileMapInfo->getTileMap()->addChild(this);

    TMXTiledMap* tmxTileMap = mTileMapInfo->getTileMap();
    Size tileSize = tmxTileMap->getTileSize();
    Size tankSize = getContentSize();

    setScale((tileSize.height * 2 - 4) / (tankSize.height));

    mBullet = Bullet::createBulletWithTank(this);
}

bool Tank::command(enumOrder order)
{
    float stepX = 0.0f;
    float stepY = 0.0f;
    float fRotation = getRotation();

    switch (order)
    {
        case cmdNothing:
            break;
        case cmdGoUP:
            stepY = 2.0f;
            fRotation = 0.0f;
            break;
        case cmdGoDown:
            stepY = -2.0f;
            fRotation = 180.0f;
            break;
        case cmdGoLeft:
            stepX = -2.0f;
            fRotation = 270.0f;
            break;
        case cmdGoRight:
            stepX = 2.0f;
            fRotation = 90.0f;
            break;
        case cmdFire:

            return mBullet->fire();
        default:
            break;
    }

    setRotation(fRotation);

    Rect rect = this->getBoundingBox();
    mMovedRect = Rect(rect.getMinX() + stepX, rect.getMinY() + stepY, rect.size.width,
            rect.size.height);
    if (!mTileMapInfo->collisionTest(mMovedRect))
    {
        IsBlock = false;
        return true;
    }

    mMovedRect = rect;
    IsBlock = true;

    return false;
}

void Tank::move()
{
    if (!IsBlock)
    {
        setPosition(Point(mMovedRect.getMidX(), mMovedRect.getMidY()));
    }
}
