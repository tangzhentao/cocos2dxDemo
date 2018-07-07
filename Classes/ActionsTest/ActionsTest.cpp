//
//  ActionsTest.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/6.
//

#include "ActionsTest.h"

USING_NS_CC;

/*
 ActionsTest
 */
ActionsTest::ActionsTest()
{
//    addTestCase("action move", []{ return new ActionMove(); });
    addTestCase("ActionMove", []() { return ActionMove::create(); });
}

/*
 ActionsDemo
 */
void ActionsDemo::onEnter()
{
    TestCase::onEnter();
    log("ActionsDemo::onEnter()");
}

void ActionsDemo::onExit()
{
    TestCase::onExit();
    log("ActionsDemo::onEnter()");
}

/*
 ActionMove
 */

void ActionMove::onEnter()
{
    TestCase::onEnter();
    log("ActionMove::onEnter()");
}
