//
//  BaseTest.h
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#ifndef BaseTest_h
#define BaseTest_h

#include <stdio.h>

class TestBase
{
public:
    virtual void runThisTest() {}

protected:
    TestBase();
    std::string _testName;
    TestBase * _parentTest;
};

#endif /* BaseTest_h */
