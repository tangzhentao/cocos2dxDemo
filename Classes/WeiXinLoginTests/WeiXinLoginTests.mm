//
//  WeiXinLoginTests.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/8.
//

#include "WeiXinLoginTests.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
#import "WXApi.h"
#import "WXApiObject.h"
#import "WXApiManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::ui;

WeiXinLoginTests::WeiXinLoginTests()
{
    addTestCase("wei xin login", []() {return WeiXinLogin::create(); } );
}

WeiXinLogin::WeiXinLogin()
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
                SendAuthReq* req = [[SendAuthReq alloc] init];
                req.scope = @"snsapi_userinfo"; // @"post_timeline,sns"
                req.state = @"xyz";
//                req.openID = openID;
                
                BOOL result =  [WXApi sendReq:req];
                if (result) {
                    log("send success");
                } else {
                    log("send failed");
                }
            }
                break;
            default:
                break;
        }
    });
    
    button->setPosition(VisibleRect::center());
    
    this->addChild(button);
    
}

std::string WeiXinLogin::title() const
{
    return "WeiXinLoginTests";
}

std::string WeiXinLogin::subtitle() const
{
    return "WeiXinLogin";
}

void WeiXinLogin::onEnter()
{
    TestCase::onEnter();
    log("ActionMove::onEnter()");
}

void WeiXinLogin::onExit()
{
    TestCase::onExit();
    log("ActionsDemo::onEnter()");
}
