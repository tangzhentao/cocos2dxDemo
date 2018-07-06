//
//  ActionsTest.h
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/6.
//

#ifndef ActionsTest_h
#define ActionsTest_h

#include <stdio.h>
#include "TestBase.h"

DEFINE_TEST_SUITE(ActionsTest);

class ActionsDemo: public TestCase
{
protected:
    cocos2d::Sprite*    _grossini;
    cocos2d::Sprite*    _tamara;
    cocos2d::Sprite*    _kathia;
    
public:
    virtual void onEnter() override;
    virtual void onExit() override;

};

class ActionMove: public ActionsDemo
{
public:
    CREATE_FUNC(ActionMove);
    virtual void onEnter() override;
    
private:
    std::string _name;
};

#endif /* ActionsTest_h */
