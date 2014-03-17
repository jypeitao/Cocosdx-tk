#ifndef __ENEMY__AI__H__
#define __ENEMY__AI__H__

#include "cocos2d.h"
using namespace cocos2d;
#include "Tank.h"

static const char* enemyTankType[] =
{
    "normalU.png",
    "speedU.png",
    "armor1U.png" };

class EnemyAI
{
public:
    EnemyAI();
    ~EnemyAI();

    static EnemyAI* createEnemyAIWithTank(Tank* tank);
    void initEnemyAIWithTank(Tank* tank);
    void update(float delta);

    void collisionTest();


private:
    void addTank(float delta);
    void tankAction(float delta);

private:
    __Array* mEnemyTanks;
    Tank* mTank;
    TileMapInfo* mTileMapInfo;

    Point bornPoint[3];
};

#endif
