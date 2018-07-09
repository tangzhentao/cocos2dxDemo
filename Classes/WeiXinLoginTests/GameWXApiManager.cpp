//
//  GameWXApiManager.cpp
//  cocos2dxDemo
//
//  Created by tang on 2018/7/8.
//

#include "GameWXApiManager.h"

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
    
}

void GameWXApiManager::onResp()
{
    log("GameWXApiManager::onResp()");
}
