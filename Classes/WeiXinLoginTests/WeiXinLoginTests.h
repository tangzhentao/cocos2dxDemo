//
//  WeiXinLoginTests.h
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/8.
//

#ifndef WeiXinLoginTests_h
#define WeiXinLoginTests_h

#include <stdio.h>
#include "TestBase.h"

DEFINE_TEST_SUITE(WeiXinLoginTests);

class WeiXinLogin: public TestCase
{
public:
    CREATE_FUNC(WeiXinLogin);
    WeiXinLogin();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual void onEnter() override;
    virtual void onExit() override;

private:
	
};

#endif /* WeiXinLoginTests_h */
