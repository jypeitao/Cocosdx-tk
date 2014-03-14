#include "HelloWorldScene.h"
#include "ChoiceScene.h"

USING_NS_CC;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();

    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed,this);
    keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased,this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));

    closeItem->setPosition(
            Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                    origin.y + visibleSize.height - closeItem->getContentSize().height / 2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto itemPlay = MenuItemImage::create("playgameNormal.png", "playgameClose.png",
            CC_CALLBACK_1(HelloWorld::menuPlayGameCallback,this));
    itemPlay->setPosition(Point(visibleSize.width / 2, visibleSize.height * 1.0f / 4.0f));
    itemPlay->setScaleX(visibleSize.width / 600);
    itemPlay->setScaleY(visibleSize.height / 400);

    auto menuPlay = Menu::create(itemPlay, NULL);
    menuPlay->setPosition(Point::ZERO);
    this->addChild(menuPlay, 1);

    Sprite *bgSprite = Sprite::create("ScenceStart.png");
    bgSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    Size sz = bgSprite->getContentSize();
    bgSprite->setScaleX(visibleSize.width / sz.width);
    bgSprite->setScaleY(visibleSize.height / sz.height);
    this->addChild(bgSprite, 0);

    return true;
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuPlayGameCallback(Object* pSender)
{
    Scene* pScene = ChoiceScene::scene();
//    Director::getInstance()->setDepthTest(true);

    Director::getInstance()->replaceScene(TransitionMoveInL::create(2,pScene));
    return;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
    {
        //_label->setString("MENU clicked!");
    }
}
