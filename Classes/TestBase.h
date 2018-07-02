//
//  BaseTest.h
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#ifndef BaseTest_h
#define BaseTest_h

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

/*
 测试基类
 */
class TestBase: public cocos2d::Ref
{
public:
    virtual void runThisTest() {}
    
    bool isTestList() {return _isTestList;}

protected:
    TestBase();
    std::string _testName;
    TestBase * _parentTest;
    bool _isTestList;
    std::vector<std::string> _childTestNames;
};

/*
 测试列表
 */
class TestList: public TestBase, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    TestList();
    
    // 添加测试项
    void addTest(const std::string &name, std::function<TestBase *()> callback);
    // 重载父类的方法
    virtual void runThisTest() override;
    
private:
    std::vector< std::function<TestBase *()> > _testCallbacks;
    
};

#endif /* BaseTest_h */
