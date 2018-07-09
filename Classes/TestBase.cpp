//
//  BaseTest.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#include "TestBase.h"
#include "VisibleRect.h"
#include "ActionsTest.h"
#include "HelloWorldScene.h"

USING_NS_CC;

USING_NS_CC_EXT;

#define TABLE_LABEL_TAG 1024

/* TestBase */
TestBase::TestBase(): _parentTest(nullptr), _isTestList(false)
{
    
}

void TestBase::backsUpOneLevel()
{
    if (_parentTest) {
        auto director = Director::getInstance();
        auto prescene = director->getPreviousScene();
        auto transition = TransitionMoveInL::create(1, prescene);
        director->popSceneWithTransition(transition);
//        Director::getInstance()->popScene();
//        _parentTest->runThisTest();
        this->release();
    }
}

/* TestCustomTableView */
class TestCustomTableView: public TableView
{
public:
    static TestCustomTableView * create(TableViewDataSource *dataSource, Size size)
    {
        auto table = new(std::nothrow) TestCustomTableView();
        table -> initWithViewSize(size);
        table -> autorelease();
        table -> setDataSource(dataSource);
        
        // 不知道下面两行啥意思
        table -> _updateCellPositions();
        table -> _updateContentSize();
        
        return table;
    }
    
    /*
     触摸cell结束回调
     触摸包括：点击和滑动
     */
    virtual void onTouchEnded(Touch *touch, Event *event) override
    {
        if (!this -> isVisible())
        {
            return;
        }
        
        if (_touchedCell)
        {
            auto label = (Label *)_touchedCell -> getChildByTag(TABLE_LABEL_TAG);
            
            // 判断有没有点中label
            Rect bbox = label -> getBoundingBox();
            bbox.origin = _touchedCell -> convertToWorldSpace(bbox.origin);
            
            if (bbox.containsPoint(touch->getLocation()))
            {
                // 告诉代理cell按下后被释放了
                _tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
                // 告诉代理cell被touch了
                _tableViewDelegate->tableCellTouched(this, _touchedCell);
            }
            
            _touchedCell = nullptr;
        }
        
        ScrollView::onTouchEnded(touch, event);
    }
    
    // 鼠标事件
    void onMouseScroll(Event *event)
    {
        
    }
    
protected:
    TestCustomTableView()
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener -> onMouseScroll = CC_CALLBACK_1(TestCustomTableView::onMouseScroll, this);
        _eventDispatcher -> addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
};

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
    auto origion = director->getVisibleOrigin();
    auto size = director->getVisibleSize();
    
    // 创建一个场景
    _scene = Scene::create();
    
    auto bgLayer = LayerColor::create(Color4B::GRAY);
    _scene->addChild(bgLayer, -1);
    
    // 创建tableview
    auto tableSize = Size(400, size.height - 20);
    auto table = TestCustomTableView::create(this, Size(400, size.height - 20));
    // 把tableview放在中间，tableview是Layer的子类，Layer的锚点anchor在左下角
    auto tablePosition = Vec2(origion.x + (size.width - tableSize.width)/2, (size.height - tableSize.height)/2 );
    table->setPosition(tablePosition);
    table->setColor(Color3B::GREEN);
    table->setDirection(ScrollView::Direction::VERTICAL); // tableview垂直方向上滚动
    table->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN); // 好像是数据填充顺序：从上往下
    table->setDelegate(this);
    // tableview添加到场景中
    _scene->addChild(table, 1);
    // 加载数据
    table->reloadData();
    
    if (_parentTest)
    {// 存在上一级测试，显示返回按钮
        
        // 添加返回上一级按钮
        TTFConfig ttfConfig("fonts/Marker Felt.ttf", 20 );
        auto backLabel = Label::createWithTTF(ttfConfig, "back");
        auto backItem = MenuItemLabel::create( backLabel, std::bind(&TestBase::backsUpOneLevel, this) );
        auto menu = Menu::createWithItem(backItem);
        
        backItem->setPosition(origion.x + size.width - backItem->getContentSize().width/2, origion.y + backItem->getContentSize().height / 2);
        menu->setPosition(Vec2::ZERO);
        
        _scene->addChild(menu, 1);
    } else
    {// 没有上一级测试
        
        // 添加自动测试按钮和关闭按钮
        auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [&](Ref *sender){
            Director::getInstance()->end();
            if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
                exit(0);
            }
        });
        closeItem->setPosition(VisibleRect::right().x - 30, VisibleRect::top().y - 30);
        
        auto autoTestLabel = Label::createWithTTF("start auto test", "fonts/Marker Felt.ttf", 20);
        auto autoTestItem = MenuItemLabel::create(autoTestLabel, std::bind(&TestList::startAutoTest, this));
        autoTestItem->setPosition(VisibleRect::left().x + autoTestItem->getContentSize().width/2, VisibleRect::bottom().y + autoTestItem->getContentSize().height/2);
        
        auto menu = Menu::create(autoTestItem, closeItem, NULL);
        menu->setPosition(Vec2::ZERO);

        _scene->addChild(menu, 1);
        
    }
    
    director->replaceScene(_scene);
}

void TestList::startAutoTest()
{
    log("自动测试稍后再写。");
}

// TableViewDataSource
 ssize_t TestList::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _childTestNames.size();
}

TableViewCell *TestList::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell =TableViewCell::create();
        auto label = Label::createWithTTF(_childTestNames[idx], "fonts/arial.ttf", 20.0f);
        label->setTag(TABLE_LABEL_TAG);
        label->setPosition(Vec2(200, 15));
        label->setColor(Color3B::GREEN);
        cell->addChild(label);
        cell->setColor(Color3B::ORANGE);
    } else
    {
        auto label = (Label *)cell->getChildByTag(TABLE_LABEL_TAG);
        label->setString(_childTestNames[idx]);
    }
    
    return cell;
}

Size TestList::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(400, 30);
}

// TableViewDelegate
void TestList::tableCellTouched(TableView *table,TableViewCell *cell)
{
//    auto test = TestCase::create();
//    
//    Director::getInstance()->replaceScene(test);
//    return;
    
//    auto label = (Label *)cell->getChildByTag(TABLE_LABEL_TAG);
//
//    auto cellPosition = cell->getPosition();
//    auto cellSize = cell->getContentSize();
//
//    auto labelPosition = label->getPosition();
//    auto labelSize = label->getContentSize();
//
//    log("cell: [(%f, %f), (%f, %f)]", cellPosition.x, cellPosition.y, cellSize.width, cellSize.height);
//    log("label: [(%f, %f), (%f, %f)]", labelPosition.x, labelPosition.y, labelSize.width, labelSize.height);
//
//    auto director = Director::getInstance();
//    auto origin = director->getVisibleOrigin();
//    auto size = director->getVisibleSize();
//
//    auto sizeWin = director->getWinSize();
//
//    log("visible: [(%f, %f), (%f, %f)]", origin.x, origin.y, size.width, size.height);
//    log("win: [(%f, %f), (%f, %f)]", origin.x, origin.y, sizeWin.width, sizeWin.height);
//
//    auto scenOrigin = _scene->getPosition();
//    auto scenSize = _scene->getContentSize();
//    log("scene: [(%f, %f), (%f, %f)]", scenOrigin.x, scenOrigin.y, scenSize.width, scenSize.height);
    
    ssize_t index = cell->getIdx();
    auto callback = _testCallbacks[index];
    if (callback) {
        auto test = callback();
        if (test->getChildTestCount() > 0) {
            // 设置标题 省略
            test->setParentTest(this);
            test->runThisTest();
        }
    }
}

/*
 TestCase类
 */
TestCase::TestCase(): _testSuite(nullptr)
{
    log("TestCase::TestCase()");
}

TestCase::~TestCase()
{
    log("TestCase::~TestCase()");
}

bool TestCase::init()
{
    if (Scene::init())
    {
        // 背景
        auto bg = LayerColor::create(Color4B::GREEN);
        addChild(bg, -1);
        
        // 添加标题和子标题
        TTFConfig ttfconfig("fonts/arial.ttf", 26.0f);

        _titleLabel = Label::createWithTTF(ttfconfig, title());
        _titleLabel->setPosition(VisibleRect::center().x, VisibleRect::top().y - 30);
        addChild(_titleLabel, 1);
        
        ttfconfig.fontSize = 16;
        _subtitleLabel = Label::createWithTTF(ttfconfig, subtitle());
        _subtitleLabel->setPosition(VisibleRect::center().x, VisibleRect::top().y - 60);
        addChild(_subtitleLabel, 1);


        // 添加菜单
        ttfconfig.fontSize = 20;
        auto previousLabel = Label::createWithTTF(ttfconfig, "previous");
        auto restartLabel = Label::createWithTTF(ttfconfig, "restart");
        auto nextLabel = Label::createWithTTF(ttfconfig, "next");
        auto backLabel = Label::createWithTTF(ttfconfig, "back");

        _previousItem = MenuItemLabel::create(previousLabel, std::bind(&TestCase::previousCallback, this));
        _restartItem = MenuItemLabel::create(restartLabel, std::bind(&TestCase::restartCallback, this));
        _nextItem = MenuItemLabel::create(nextLabel, std::bind(&TestCase::nextCallback, this));
        auto backItem = MenuItemLabel::create(backLabel, std::bind(&TestCase::backCallback, this));

        
        auto restartPositon = Vec2();
        restartPositon.x = VisibleRect::bottom().x;
        restartPositon.y = VisibleRect::bottom().y + restartLabel->getContentSize().height / 2;
        _restartItem->setPosition(restartPositon);
        
        auto previousPositon = Vec2();
        auto previousSize = _previousItem->getContentSize();
        float space = 10;
        previousPositon.x = restartPositon.x - _restartItem->getContentSize().width/2 - previousSize.width / 2 - space;
        previousPositon.y = restartPositon.y;
        _previousItem->setPosition(previousPositon);

        auto nextPositon = Vec2();
        auto nextSize = _nextItem->getContentSize();
        nextPositon.x = restartPositon.x + _restartItem->getContentSize().width/2 + nextSize.width / 2 + space;
        nextPositon.y = restartPositon.y;
        _nextItem->setPosition(nextPositon);
        
        auto backPositon = Vec2();
        auto backSize = backItem->getContentSize();
        backPositon.x = VisibleRect::right().x - backSize.width;
        backPositon.y = VisibleRect::bottom().y + backSize.height / 2;
        backItem->setPosition(backPositon);

        auto menu = Menu::create(_previousItem, _restartItem, _nextItem, backItem, NULL);
        menu->setPosition(Vec2::ZERO);
        
        addChild(menu, 1);
        
        return true;
    }
    
    return false;
}

void TestCase::onEnter()
{
    Scene::onEnter();
}

void TestCase::previousCallback()
{
    log("TestCase::previousCallback()");
}

void TestCase::restartCallback()
{
    log("TestCase::restartCallback()");
}

void TestCase::nextCallback()
{
    log("TestCase::nextCallback()");
}

void TestCase::backCallback()
{
    log("TestCase::backCallback()");
    if (_testSuite) {
        _testSuite->backsUpOneLevel();
    }
}

/*
 测试套件类
 */
TestSuite::TestSuite(): _currentIndex(0)
{
    
}

void TestSuite::addTestCase(const std::string &testName, std::function<cocos2d::Scene *()> callback)
{
    if (!testName.empty() && callback) {
        _childTestNames.emplace_back(testName);
        _testCallbacks.emplace_back(callback);
    }
}

void TestSuite::runThisTest()
{
    if (!_childTestNames.empty()) {
        auto scene = _testCallbacks[_currentIndex]();
        
        auto testCase = dynamic_cast<TestCase *>(scene);
        testCase->setTestSuite(this);
        auto director = Director::getInstance();
        auto transition = TransitionMoveInR::create(0.5, testCase);
        director->pushScene(transition);
    }
}

void TestSuite::previous()
{
    log("TestSuite::previou()");
}

void TestSuite::restart()
{
    log("TestSuite::restart()");
}

void TestSuite::next()
{
    log("TestSuite::next()");
}
