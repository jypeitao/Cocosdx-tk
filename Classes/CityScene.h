#ifndef __CITYSCENE__H__
#define __CITYSCENE__H__

#include <cocos2d.h>
using namespace cocos2d;

#include "Tank.h"
#include "Panel.h"
#include "TileMapInfo.h"
#include "EnemyAI.h"

class CityScene: public Layer
{
public:
    CityScene();
    ~CityScene();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void update(float delta) override;

    static Scene *scene();
    static Scene *scene(int round);
    //
    CREATE_FUNC(CityScene)
    ;
    static CityScene *create(int round);
    //
CC_SYNTHESIZE(int, mRound, Round)
    ;

private:
	Tank* mPlayerTank[2];
	Panel* mLayerPanel;
	EnemyAI* mEnemyAI;
};

#endif
