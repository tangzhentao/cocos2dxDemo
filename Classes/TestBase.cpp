//
//  BaseTest.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#include "TestBase.h"

USING_NS_CC;

/* TestBase */
TestBase::TestBase(): _parentTest(nullptr), _isTestList(false)
{
    
}

/* TestList */
TestList::TestList()
{
    
}

void TestList::addTest(const std::string &name, std::function<TestBase *()> callback)
{
    if (!name.empty())
    {
        _childTestNames.emplace_back(name);
        _testCallbacks.emplace_back(callback);
    }
}

void TestList::runThisTest()
{
    auto director = Director::getInstance();
    
//    auto =  ui::tab
}
