//
//  GameWXApiManager.cpp
//  cocos2dxDemo
//
//  Created by tang on 2018/7/8.
//

#include "GameWXApiManager.h"
#import "WXApiManager.h"

USING_NS_CC;

static GameWXApiManager *s_sharedGameWXApiManager = nullptr;

GameWXApiManager * GameWXApiManager::getInstance()
{
    if (nullptr == s_sharedGameWXApiManager)
    {
        s_sharedGameWXApiManager = new (std::nothrow) GameWXApiManager;
    }
    
    return s_sharedGameWXApiManager;
}

GameWXApiManager::GameWXApiManager()
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

void GameWXApiManager::weixinLogin()
{
    log("GameWXApiManager::weixinLogin()");
    
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

void GameWXApiManager::onResp(int errCode, const std::string &errStr, const std::string &data)
{
    log("GameWXApiManager::onResp()");
    
    if (0 == errCode)
    {/**< 成功    */
        log("成功");
        if (_delgate) {
            _delgate->managerDidRecvAuthResponse(data);
        }
    } else if (-1 == errCode)
    {/**< 普通错误类型    */
        log("普通错误类型");

    } else if (-2 == errCode)
    {/**< 用户点击取消并返回    */
        log("用户点击取消并返回");

    } else if (-3 == errCode)
    {/**< 发送失败    */
        log("发送失败");

    } else if (-4 == errCode)
    {/**< 授权失败    */
        log("授权失败");

    }
}
