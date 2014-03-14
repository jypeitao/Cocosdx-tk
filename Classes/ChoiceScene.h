#ifndef __CHOICE__SCENE__H__
#define __CHOICE__SCENE__H__

#include "cocos2d.h"

class ChoiceScene: public cocos2d::Layer
{
public:
    ChoiceScene();
    virtual bool init() override;
    //
    CREATE_FUNC(ChoiceScene)
    ;
    static cocos2d::Scene *scene();

    void touchAction(Node *n);
private:
    void update(float f) override;
    void updateRound();
    int mRound;
};

#endif
