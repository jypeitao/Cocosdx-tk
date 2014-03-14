#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
using namespace cocos2d;
#include "Tank.h"

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	static Bullet* createBulletWithTank(Tank* tank);
	void initBulletWithTank(Tank* tank);
	bool fire();
	virtual void update(float delta) override;
	void bulletBoom();

private:
	bool isFlying;
	Tank* mTank;
	TileMapInfo* mTileMapInfo;
	float stepX, stepY;

	CC_SYNTHESIZE(Rect, mMovedRect, MovedRect);
};

#endif
