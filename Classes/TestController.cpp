//
//  TestController.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#include "TestController.h"

static TestController *s_testController = nullptr;
TestController * TestController::getInstance()
{
    if (nullptr == s_testController)
    {
        s_testController = new(std::nothrow) TestController;
    }
    return s_testController;
}

TestController::TestController()
{
    
}
