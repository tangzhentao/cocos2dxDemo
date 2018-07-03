//
//  TestController.h
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#ifndef TestController_h
#define TestController_h

#include <stdio.h>

class TestList;

/*
 使用静态成员函数和私有构造函数来实现单例
 */
class TestController
{
public:
    static TestController *getInstance();
    
    ~TestController();

private:
    TestController();
    
    TestList *_rootTestList;
};

#endif /* TestController_h */
