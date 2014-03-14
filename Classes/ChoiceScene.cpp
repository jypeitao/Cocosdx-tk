#include "ChoiceScene.h"
#include "Paddle.h"
#include "CommonValue.h"
#include "CityScene.h"

using namespace cocos2d;

#define TOTAL_ROUNDS   20

ChoiceScene::ChoiceScene() :
                mRound(1)
{

}

Scene *ChoiceScene::scene()
{
    Scene *scene = Scene::create();
    ChoiceScene *layer = ChoiceScene::create();
    if (scene && layer)
    {
        scene->addChild(layer);
    }

    return scene;
}

bool ChoiceScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size szWin = Director::getInstance()->getWinSize();

    Sprite *pSprite = Sprite::create("Black.png");
    Size szSprite = pSprite->getContentSize();
    pSprite->setScaleX(szWin.width / szSprite.width);
    pSprite->setScaleY(szWin.height / szSprite.height);
    pSprite->setPosition(Point(szWin.width / 2, szWin.height / 2));
    this->addChild(pSprite, 0);

    const char *szImgs[4] =
    {
            "paddle/btn_play.png",
            "paddle/btn_rewind.png",
            "paddle/btn_fast_forward.png",
            "fonts/fps_images.png" };

    float fSettings[4][4] =
    {
            {
                    20.0f / 480,
                    16.0f / 320,
                    280.0f / 480,
                    160.0f / 320 },
            {
                    20.0f / 480,
                    16.0f / 320,
                    200.0f / 480,
                    160.0f / 320 },
            {
                    20.0f / 480,
                    16.0f / 320,
                    240.0f / 480,
                    160.0f / 320 },
            {
                    20.0f / 480,
                    22.0f / 320,
                    280.0f / 480,
                    172.0f / 320 } };

//    enum_evt evts[4] =
//    {
//            evt_start,
//            evt_pressA,
//            evt_pressB,
//            evt_text };

    for (int i = 0; i < 3; ++i)
    {
        float* fSetting = fSettings[i];
        Texture2D* paddleTexture = Director::getInstance()->getTextureCache()->addImage(szImgs[i]);
        Paddle* pPaddle = Paddle::paddleWithTexture(paddleTexture);
        Size szBtn = pPaddle->getContentSize();
        pPaddle->setScaleX(szWin.width / szBtn.width * fSetting[0]);
        pPaddle->setScaleY(szWin.height / szBtn.height * fSetting[1]);
        pPaddle->setPosition(Point(szWin.width * fSetting[2], szWin.height * fSetting[3]));
        pPaddle->setTag(i);
        pPaddle->onAction = CC_CALLBACK_1(ChoiceScene::touchAction,this);
        addChild(pPaddle);

        //pPaddle->setpSence(this);
        //pPaddle->setevttyp(evts[i]);
    }

    int i = 3;
    Color3B color =
    {
            0,
            0,
            0 };
    float* fSetting = fSettings[i];
    LabelAtlas* label1 = LabelAtlas::create("1", szImgs[i], 16, 32, '.');

    Size sz = label1->getContentSize();
    label1->setAnchorPoint(Point(0.5f, 0.5f));
    label1->setScaleX(szWin.width / sz.width * fSetting[0]);
    label1->setScaleY(szWin.height / sz.height * fSetting[1]);
    label1->setPosition(Point(szWin.width * fSetting[2], szWin.height * fSetting[3]));
    label1->setColor(color);
//    addChild(label1, 0, evt_text);
    addChild(label1, 0, 4);

    //this->scheduleUpdate();
    log("updat11e");
    return true;
}

//void ChoiceScene::keyBackClicked(void)
//{
//
//}
//
//void ChoiceScene::keyMenuClicked(void)
//{
//
//}

void ChoiceScene::touchAction(Node *n)
{
    switch (n->getTag())
    {
        case 0:
        {
            auto scene = CityScene::scene(mRound);
            Director::getInstance()->replaceScene(scene);
        }
            break;
        case 1:
            if (mRound > 1)
            {
                mRound--;
                updateRound();
            }

            break;
        case 2:
            if (mRound < TOTAL_ROUNDS)
            {
                mRound++;
                updateRound();
            }

            break;
        default:
            break;
    }
//    if (controlEvent == evt_pressA)
//    {
//        mRound = 1 + (mRound - 1 + ROUNDS - 1) % ROUNDS;
//        update();
//    }
//    else if (controlEvent == evt_pressB)
//    {
//        mRound = 1 + (mRound + 1 + ROUNDS - 1) % ROUNDS;
//        update();
//    }
//    else if (controlEvent == evt_start)
//    {
//
//        Scene* scene = CityScene::scene(mRound);
//        Director::getInstance()->replaceScene(scene);
//    }
}

void ChoiceScene::update(float t)
{
    char szTemp[260];
    LabelAtlas* label1 = (LabelAtlas*) getChildByTag(4);
    sprintf(szTemp, "%d", mRound);
    label1->setString(szTemp);
    //log("update");
}

void ChoiceScene::updateRound()
{
    char szTemp[260];
    LabelAtlas* label1 = (LabelAtlas*) getChildByTag(4);
    sprintf(szTemp, "%d", mRound);
    label1->setString(szTemp);
    log("update");
}

