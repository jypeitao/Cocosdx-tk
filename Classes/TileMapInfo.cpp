#include "TileMapInfo.h"

void TileMapInfo::initMapInfoWithFile(const char* tmxFile)
{
    mTMXTileMap = TMXTiledMap::create(tmxFile);
    mTMXLayers[0] = mTMXTileMap->getLayer("layer_0");
    mTMXLayers[1] = mTMXTileMap->getLayer("layer_1");

    Size winSize = Director::getInstance()->getWinSize();
    Size mapSize = mTMXTileMap->getContentSize();

    mTMXTileMap->setScale(winSize.height / mTMXTileMap->getContentSize().height);

    mTMXTileMap->setPosition(
            Point((winSize.width - mapSize.width * mTMXTileMap->getScale()) / 2,
                    (winSize.height - mapSize.height * mTMXTileMap->getScale()) / 2));
}

TileMapInfo* TileMapInfo::createMapInfoWithFile(const char* tmxFile)
{
    TileMapInfo* tileMapInfo = new TileMapInfo();
    tileMapInfo->initMapInfoWithFile(tmxFile);

    return tileMapInfo;
}

bool TileMapInfo::collisionTest(Rect rect)
{
    int gid = 0;
    Size mapSize = mTMXTileMap->getContentSize();
    Size tileSize = mTMXTileMap->getTileSize();

    if (rect.getMinX() <= 0.1 || rect.getMaxX() >= mapSize.width || rect.getMinY() <= 0.1
            || rect.getMaxY() >= mapSize.height)
        return true;

    float MinY = mapSize.height - rect.getMinY();
    float MaxY = mapSize.height - rect.getMaxY();

    gid = mTMXLayers[0]->getTileGIDAt(
            Point((int) (rect.getMinX() / tileSize.width), (int) (MinY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->getTileGIDAt(
            Point((int) (rect.getMinX() / tileSize.width), (int) (MaxY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->getTileGIDAt(
            Point((int) (rect.getMaxX() / tileSize.width), (int) (MaxY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->getTileGIDAt(
            Point((int) (rect.getMaxX() / tileSize.width), (int) (MinY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;

    return false;
}
