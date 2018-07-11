//
//  GameWXApiManager.h
//  cocos2dxDemo
//
//  Created by tang on 2018/7/8.
//

#ifndef GameWXApiManager_h
#define GameWXApiManager_h

#include <stdio.h>
#include "cocos2d.h"


class GameWXApiManagerDelegate
{
public:
    virtual void managerDidRecvAuthResponse(const std::string &response) = 0;
};


/*
 游戏端的微信api管理器，用于桥接iOS端WXApiManager
 */
class GameWXApiManager: public cocos2d::Ref
{
public:
    static GameWXApiManager* getInstance();
    
    void weixinLogin();
    void onResp(int errCode, const std::string &errStr, const std::string &data);
    
    void setDelegate(GameWXApiManagerDelegate * delgate) { _delgate = delgate; }

private:
    GameWXApiManager();
    
    GameWXApiManagerDelegate *_delgate;
};

#endif /* GameWXApiManager_h */
