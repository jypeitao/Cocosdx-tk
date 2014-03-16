#include "Bullet.h"

Bullet::Bullet() :
                isFlying(false),
                mTank(NULL),
                mTileMapInfo(NULL),
                stepX(0),
                stepY(0)
{
}

Bullet::~Bullet()
{

}

Bullet* Bullet::createBulletWithTank(Tank* tank)
{
    Bullet* bullet = new Bullet();
    bullet->initBulletWithTank(tank);
    bullet->autorelease();

    return bullet;
}

void Bullet::initBulletWithTank(Tank* tank)
{
    mTank = tank;
    mTileMapInfo = mTank->getTileMapInfo();

    initWithSpriteFrameName("bullet.png");
    mTileMapInfo->getTileMap()->addChild(this);
    setVisible(false);
}

bool Bullet::fire()
{
    if (!isFlying)
    {
        isFlying = true;
        setVisible(true);
        setPosition(mTank->getPosition());
        int Rotation = mTank->getRotation();
        switch (Rotation)
        {
            case 0:
                stepX = 0.0f, stepY = 4.0f;
                break;
            case 90:
                stepX = 4.0f, stepY = 0.0f;
                break;
            case 180:
                stepX = 0.0f, stepY = -4.0f;
                break;
            case 270:
                stepX = -4.0f, stepY = 0.0f;
                break;
            default:
                break;
        }
        scheduleUpdate();
    }

    return isFlying;
}

void Bullet::bulletBoom()
{
    Rect rect = getBoundingBox();
    Size mapSize = mTileMapInfo->getTileMap()->getContentSize();

    if (rect.getMinX() < 0 || rect.getMaxX() >= mapSize.width || rect.getMinY() < 0
            || rect.getMaxY() >= mapSize.height)
        return;

    TMXLayer* tmxLayer = mTileMapInfo->getTileMap()->getLayer("layer_0");
    Size tileSize = tmxLayer->getMapTileSize();


    float MinY = mapSize.height - rect.getMinY();
    float MaxY = mapSize.height - rect.getMaxY();


    Point pt = Point((int) rect.getMinX() / tileSize.width, (int) (MinY / tileSize.height));
    if (gidToTileType[tmxLayer->getTileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);

    pt = Point((int) rect.getMinX() / tileSize.width, (int) (MaxY / tileSize.height));
    if (gidToTileType[tmxLayer->getTileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);

    pt = Point((int) rect.getMaxX() / tileSize.width, (int) (MinY / tileSize.height));
    if (gidToTileType[tmxLayer->getTileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);

    pt = Point((int) rect.getMaxX() / tileSize.width, (int) (MaxY / tileSize.height));
    if (gidToTileType[tmxLayer->getTileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);
}

void Bullet::update(float delta)
{
    Sprite::update(delta);

    setPosition(Point(getPositionX() + stepX, getPositionY() + stepY));

    Rect rect = getBoundingBox();
    if (mTileMapInfo->collisionTest(rect))
    {
        unscheduleUpdate();
        setVisible(false);
        isFlying = false;

        bulletBoom();
    }
}

