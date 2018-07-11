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
#include "GameWXApiManager.h"
#include "network/HttpClient.h"

DEFINE_TEST_SUITE(WeiXinLoginTests);

class CCProgressLayer;

class WeiXinLogin: public TestCase, public GameWXApiManagerDelegate
{
public:
    CREATE_FUNC(WeiXinLogin);
    WeiXinLogin();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    virtual void onEnter() override;
    virtual void onExit() override;
    
    // 实现协议方法
    virtual void managerDidRecvAuthResponse(const std::string &response) override;
    
    void onHttpRequstCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
private:
    CCProgressLayer *_progressLayer;
};

#endif /* WeiXinLoginTests_h */
