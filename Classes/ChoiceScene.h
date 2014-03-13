#ifndef __CHOICE__SCENE__H__
#define __CHOICE__SCENE__H__

#include "cocos2d.h"

class ChoiceScene: public cocos2d::Layer
{
public:
    ChoiceScene();
    virtual bool init();
    //
    CREATE_FUNC(ChoiceScene)
    ;
    static cocos2d::Scene *scene();

    void touchDownAction(Object* sender, unsigned int controlEvent);
private:
    void update(float f);
    int mRound;
};

#endif
