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
    
    // 返回到上一级
    void backsUpOneLevel();
    
    bool isTestList() {return _isTestList;}
    
    size_t getChildTestCount() { return _childTestNames.size(); }
    
protected:
    TestBase();
    std::string _testName;
    TestBase * _parentTest;
    bool _isTestList;
    std::vector<std::string> _childTestNames;
};

/*
 测试列表类
 */
class TestList: public TestBase, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    TestList();
    
    // 添加测试项
    void addTest(const std::string &name, std::function<TestBase *()> callback);
    // 重载父类的方法
    virtual void runThisTest() override;
    void startAutoTest();

    
    // TableViewDataSource
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
    virtual cocos2d::extension::TableViewCell *tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView* table, ssize_t idx) override;
    
    // TableViewDelegate
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
    
private:
    std::vector< std::function<TestBase *()> > _testCallbacks;
    
    cocos2d::Scene *_scene;
    
};

class TestSuite;

/*
 测试用例
 */
class TestCase: public TestBase, public cocos2d::Scene
{
public:
    TestCase();
    ~TestCase();
    
    void setTestSuite(TestSuite *testSuite) {_testSuite = testSuite;}
    TestSuite *getTestSuite () {return _testSuite;}
    
    virtual void previous();
    virtual void restart();
    virtual void next();
    
private:
    TestSuite * _testSuite;
    
};

/*
 测试套件：包含多个测试用例
 */
class TestSuite: public TestBase
{
public:
    TestSuite();
    
    void addTestCase(std::string &testName, std::function<cocos2d::Scene *()> callback);
    
    virtual void previous();
    virtual void restart();
    virtual void next();
    
    int getCurrentIndex() { return 0; }
    
    virtual void runThisTest() override;
    
private:
    int _currentIndex;

};


#endif /* BaseTest_h */
