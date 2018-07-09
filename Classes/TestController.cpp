//
//  TestController.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#include "TestController.h"
#include "TestBase.h"
#include "ActionsTest.h"
#include "WeiXinLoginTests.h"

/*
 根测试类
 */
class RootTest: public TestList
{
public:
    RootTest()
    {
        addTest("hello world", []() {return new ActionsTest;} );
        addTest("wei xin", []() {return new WeiXinLoginTests;} );

    }
};

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
    _rootTestList = new(std::nothrow) RootTest;
    
    _rootTestList->runThisTest();
}

TestController::~TestController()
{
    _rootTestList->release();
    _rootTestList = nullptr;
}

