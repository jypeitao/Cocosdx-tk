#include "CityScene.h"

CityScene::CityScene() :
                mRound(1),
                mLayerPanel(NULL),
                mEnemyAI(nullptr)
{
    mPlayerTank[0] = NULL;
    mPlayerTank[1] = NULL;
}

CityScene::~CityScene()
{

}

bool CityScene::init()
{
    Layer::init();

    char szRound[260];
    sprintf(szRound, "Round%d.tmx", mRound);
    TileMapInfo* tileMapInfo = TileMapInfo::createMapInfoWithFile(szRound);
    TMXTiledMap* tmxTileMap = tileMapInfo->getTileMap();
    this->addChild(tmxTileMap);

    mPlayerTank[0] = Tank::createTankWithTankType("player2U.png", tileMapInfo);

    mPlayerTank[0]->setObjType(PlayerTank);
    mPlayerTank[0]->getBullet();


    Size tileSize = tmxTileMap->getTileSize();
    Size mapSize = tmxTileMap->getContentSize();
    mPlayerTank[0]->setPosition(Point(mapSize.width / 2 - tileSize.width * 3, tileSize.height));

//
    mLayerPanel = Panel::create();
    addChild(mLayerPanel, 3);
//
    mEnemyAI = EnemyAI::createEnemyAIWithTank(mPlayerTank[0]);

    return true;
}

Scene *CityScene::scene()
{
    Scene* scene = Scene::create();
    CityScene* layer = CityScene::create();

    if (scene && layer)
    {
        scene->addChild(layer);
    }

    return scene;
}

Scene *CityScene::scene(int round)
{
    Scene* scene = Scene::create();
    CityScene* layer = CityScene::create(round);

    scene->addChild(layer);

    return scene;
}

CityScene *CityScene::create(int round)
{
    CityScene* pRet = new CityScene();
    if (pRet)
    {
        pRet->setRound(round);
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
    }

    return NULL;
}

void CityScene::onEnter()
{
    Layer::onEnter();
    this->scheduleUpdate();
}

void CityScene::update(float delta)
{
    Layer::update(delta);
    if (mPlayerTank[0] != NULL)
        mPlayerTank[0]->command(mLayerPanel->getOrder());
//
    mEnemyAI->update(delta);
}
