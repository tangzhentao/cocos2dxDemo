//
//  ActionsTest.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/6.
//

#include "ActionsTest.h"
#include "CCProgressLayer.h"
#include "VisibleRect.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
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
std::string ActionsDemo::title() const
{
    return "action tests";
}
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
ActionMove::ActionMove()
{
    auto button = Button::create();
    button->setTitleText("wei xin login");
    button->setTitleFontSize(20);
    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCProgressLayer *layer = CCProgressLayer::create();
                this->addChild(layer, 1);
                layer->show();
            }
                break;
            default:
                break;
        }
    });
    
    button->setPosition(VisibleRect::center());
    
    this->addChild(button);
}

std::string ActionMove::subtitle() const
{
    return "move to/move by";
}

void ActionMove::onEnter()
{
    TestCase::onEnter();
    log("ActionMove::onEnter()");
}
