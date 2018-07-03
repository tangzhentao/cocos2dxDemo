//
//  BaseTest.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/1.
//

#include "TestBase.h"

USING_NS_CC;

USING_NS_CC_EXT;

#define TABLE_LABEL_TAG 1024

/* TestBase */
TestBase::TestBase(): _parentTest(nullptr), _isTestList(false)
{
    
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
    auto scene = Scene::create();
    
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
    scene->addChild(table, 1);
    // 加载数据
    table->reloadData();
    
    director->replaceScene(scene);
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
    
}
