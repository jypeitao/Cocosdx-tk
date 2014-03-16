#include "Panel.h"

enum paddleType
{
    paddleUp = 1,
    paddleDown,
    paddleLeft,
    paddleRight,
    paddleFire
};

bool Panel::init()
{
    Layer::init();

    Texture2D* paddleTexture = Director::getInstance()->getTextureCache()->addImage(RES_PADDLE_UP);
    m_pPaddleUp = Paddle::paddleWithTexture(paddleTexture);
    m_pPaddleUp->setTag(paddleUp);
    m_pPaddleUp->onAction = CC_CALLBACK_1(Panel::touchAction,this);

    paddleTexture = Director::getInstance()->getTextureCache()->addImage(RES_PADDLE_DOWN);
    m_pPaddleDown = Paddle::paddleWithTexture(paddleTexture);
    m_pPaddleDown->setTag(paddleDown);
    m_pPaddleDown->onAction = CC_CALLBACK_1(Panel::touchAction,this);

    paddleTexture = Director::getInstance()->getTextureCache()->addImage(RES_PADDLE_LEFT);
    m_pPaddleLeft = Paddle::paddleWithTexture(paddleTexture);
    m_pPaddleLeft->setTag(paddleLeft);
    m_pPaddleLeft->onAction = CC_CALLBACK_1(Panel::touchAction,this);

    paddleTexture = Director::getInstance()->getTextureCache()->addImage(RES_PADDLE_RIGHT);
    m_pPaddleRight = Paddle::paddleWithTexture(paddleTexture);
    m_pPaddleRight->setTag(paddleRight);
    m_pPaddleRight->onAction = CC_CALLBACK_1(Panel::touchAction,this);

    paddleTexture = Director::getInstance()->getTextureCache()->addImage(RES_PADDLE_FIRE);
    m_pPaddleFire = Paddle::paddleWithTexture(paddleTexture);
    m_pPaddleFire->setTag(paddleFire);
    m_pPaddleFire->onAction = CC_CALLBACK_1(Panel::touchAction,this);

    Size size = getContentSize();

    float localX[5] =
    {
            size.width * 4.5f / 26,
            size.width * 4.5f / 26,
            size.width * 2.3f / 26,
            size.width * 6.7f / 26,
            size.width * 22.0f / 26 };
    double localY[5] =
    {
            size.height * 6.7 / 26,
            size.height * 2.3 / 26,
            size.height * 4.5f / 26,
            size.height * 4.5f / 26,
            size.height * 5.0 / 26 };

    Paddle* paddle[] =
    {
            m_pPaddleUp,
            m_pPaddleDown,
            m_pPaddleLeft,
            m_pPaddleRight,
            m_pPaddleFire };
    for (size_t i = 0; i < sizeof(paddle) / sizeof(paddle[0]); ++i)
    {
        addChild(paddle[i]);
        paddle[i]->setPosition(Point(localX[i], localY[i]));
        Size szPaddle = paddle[i]->getContentSize();
        paddle[i]->setScale(size.height * 4.5f / 26 / szPaddle.height);
    }

    return true;
}

void Panel::touchAction(Node *n)
{
    switch (n->getTag())
    {
        case paddleUp:
            order = cmdGoUP;
            break;
        case paddleDown:
            order = cmdGoDown;
            break;
        case paddleLeft:
            order = cmdGoLeft;
            break;
        case paddleRight:
            order = cmdGoRight;
            break;
        case paddleFire:
            order = cmdFire;
            break;
        default:
            break;
    }
}
enumOrder Panel::getOrder()
{
    enumOrder t = order;
    order = cmdNothing;
    return t;
}

