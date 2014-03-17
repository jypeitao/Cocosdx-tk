#ifndef __TILEMAPINFO__H__
#define __TILEMAPINFO__H__

#include <cocos2d.h>
using namespace cocos2d;

enum enumTileType
{
    tileNone,
    tileGrass,
    tileSteel,
    tileWall,
    tileRiver,
    tileKing
};

static enumTileType gidToTileType[] =
{
    tileNone,

    tileNone,
    tileNone,
    tileGrass,
    tileGrass,
    tileSteel,
    tileSteel,
    tileNone,
    tileNone,
    tileGrass,
    tileGrass,
    tileSteel,
    tileSteel,

    tileWall,
    tileWall,
    tileRiver,
    tileRiver,
    tileKing,
    tileKing,
    tileWall,
    tileWall,
    tileRiver,
    tileRiver,
    tileKing,
    tileKing,

    tileKing,
    tileKing,
    tileNone,
    tileNone,
    tileNone,
    tileNone,
    tileKing,
    tileKing,
    tileNone,
    tileNone,
    tileNone,
    tileNone };

class TileMapInfo
{
public:
    virtual ~TileMapInfo()
    {
    }
    ;
    bool collisionTest(Rect rect);

    static TileMapInfo* createMapInfoWithFile(const char* tmxFile);
    void initMapInfoWithFile(const char* tmxFile);CC_SYNTHESIZE(TMXTiledMap*, mTMXTileMap, TileMap)
    ;

private:
    TMXLayer* mTMXLayers[2];
};

#endif
