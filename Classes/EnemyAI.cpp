#include "EnemyAI.h"

EnemyAI::EnemyAI() :
        mEnemyTanks(NULL),
        mTank(NULL),
        mTileMapInfo(NULL)
{

}

EnemyAI::~EnemyAI()
{

}

EnemyAI* EnemyAI::createEnemyAIWithTank(Tank* tank)
{
    EnemyAI* enemyTank = new EnemyAI();
    enemyTank->initEnemyAIWithTank(tank);

    return enemyTank;
}

void EnemyAI::initEnemyAIWithTank(Tank* tank)
{
    mTank = tank;
    mTileMapInfo = tank->getTileMapInfo();
    mEnemyTanks = Array::createWithCapacity(4);
    mEnemyTanks->retain();

    Size mapSize = mTileMapInfo->getTileMap()->getContentSize();
    Size tileSize = mTileMapInfo->getTileMap()->getLayer("layer_0")->getMapTileSize();
    bornPoint[0] = Point(tileSize.width, mapSize.height - tileSize.height);
    bornPoint[1] = Point(mapSize.width / 2, mapSize.height - tileSize.height);
    bornPoint[2] = Point(mapSize.width - tileSize.width, mapSize.height - tileSize.height);
}

void EnemyAI::update(float delta)
{
    addTank(delta);

    tankAction(delta);
}

void EnemyAI::addTank(float delta)
{
    static float deltaTimes = 0.0f;
    deltaTimes += delta;
    if (deltaTimes >= 2.0f)
    {
        deltaTimes = 0.0f;
        int count = mEnemyTanks->count();
        if (count < 3)
        {
            Tank* enemyTank = Tank::createTankWithTankType(enemyTankType[count], mTileMapInfo);
            enemyTank->setPosition(bornPoint[count]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }
        else if (count == 3)
        {
            int tankTypeIndex = (int) (CCRANDOM_0_1() * 4) % 3;
            Tank* enemyTank = Tank::createTankWithTankType(enemyTankType[tankTypeIndex],
                    mTileMapInfo);
            enemyTank->setPosition(bornPoint[tankTypeIndex]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }
    }
}

void EnemyAI::tankAction(float delta)
{
    Object* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* tank = (Tank*) pObj;

        int Rotation = tank->getRotation();
        tank->command((enumOrder) (Rotation / 90 + 1));

        tank->setBulletDelta(tank->getBulletDelta() + delta);
        if (tank->getBulletDelta() > 1)
        {

            if (tank->command(cmdFire))
            {
                tank->setBulletDelta(0.0);
            }
        }

        collisionTest();

        if (tank->getBlock())
            tank->setRotation((int) (CCRANDOM_0_1() * 3.2) * 90);

        tank->move();
    }
    mTank->move();
}

void EnemyAI::collisionTest()
{
    Object* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* enemyTank = (Tank*) pObj;
        if (IsRectIntersect(mTank->getMovedRect(), enemyTank->getMovedRect()))
        {
            enemyTank->setBlock(true);
            mTank->setBlock(true);
        }
    }

    __Array* ccTmpArray = __Array::create();
    ccTmpArray->addObjectsFromArray(mEnemyTanks);
    while (ccTmpArray->count())
    {
        Object* pObj;
        Tank* tmpTank = (Tank*) ccTmpArray->getLastObject();
        ccTmpArray->removeLastObject();
        CCARRAY_FOREACH(ccTmpArray, pObj)
        {
            if (IsRectIntersect(tmpTank->getMovedRect(), ((Tank*) pObj)->getMovedRect()))
            {
                tmpTank->setBlock(true);
                ((Tank*) pObj)->setBlock(true);
                ccTmpArray->removeObject(pObj);
            }
        }
    }
}

bool EnemyAI::IsRectIntersect(Rect rectA, Rect rectB)
{
    float left = std::max(rectA.getMinX(), rectB.getMinX());
    float right = std::min(rectA.getMaxX(), rectB.getMaxX());
    if (left > right)
        return false;

    float top = std::min(rectA.getMaxY(), rectB.getMaxY());
    float bottom = std::max(rectA.getMinY(), rectB.getMinY());
    if (top < bottom)
        return false;

    return true;
}
