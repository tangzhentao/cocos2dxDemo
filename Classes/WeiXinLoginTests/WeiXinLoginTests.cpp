//
//  WeiXinLoginTests.cpp
//  cocos2dxDemo-mobile
//
//  Created by tang on 2018/7/8.
//

#include "WeiXinLoginTests.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
#include "GameWXApiManager.h"
#include <iostream>

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/prettywriter.h" // for stringify JSON

#include "CCProgressLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d::network;

WeiXinLoginTests::WeiXinLoginTests()
{
    addTestCase("wei xin login", []() {return WeiXinLogin::create(); } );
}

WeiXinLogin::WeiXinLogin()
{
    auto button = Button::create();
    button->setTitleText("wei xin login");
    button->setTitleFontSize(20);
    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                GameWXApiManager::getInstance()->setDelegate(this);
                GameWXApiManager::getInstance()->weixinLogin();
                
//                auto spriteFrameCache = SpriteFrameCache::getInstance();
//                spriteFrameCache->addSpriteFramesWithFile("MjLoading.plist");
//                
//                for (int i = 1; i <= NumActivityIndicator; i++) {
//                    stringstream ss;
//                    ss << "MjLoading" << i << ".png";
//                    auto spriteFrame = spriteFrameCache->getSpriteFrameByName(ss.str() );
//                    _spriteFrames.pushBack(spriteFrame);
//                }
//                
//                auto sprite = Sprite::createWithSpriteFrame(_spriteFrames.front() );
//                sprite->setPosition(VisibleRect::center() );
//                this->addChild(sprite, 2);
//                
//                
//                
//                Animation * animation = Animation::createWithSpriteFrames(_spriteFrames, 1.0f/8);
//                auto animate = Animate::create(animation);
//                sprite->runAction(RepeatForever::create(animate));
            }
                break;
            default:
                break;
        }
    });
    
    button->setPosition(VisibleRect::center());
    
    this->addChild(button);
}

std::string WeiXinLogin::title() const
{
    return "WeiXinLoginTests";
}

std::string WeiXinLogin::subtitle() const
{
    return "WeiXinLogin";
}

void WeiXinLogin::onEnter()
{
    TestCase::onEnter();
    log("ActionMove::onEnter()");
}

void WeiXinLogin::onExit()
{
    TestCase::onExit();
    log("ActionsDemo::onEnter()");
}

void WeiXinLogin::managerDidRecvAuthResponse(const std::string &response)
{
    if (!response.empty())
    {// 如果response不为空，就去请求获取access_token：
        
        HttpRequest *request = new(std::nothrow) HttpRequest();
        stringstream urlStream;
        
        // "https://api.weixin.qq.com/sns/oauth2/access_token?appid=APPID&secret=SECRET&code=CODE&grant_type=authorization_code"
        urlStream << "https://api.weixin.qq.com/sns/oauth2/access_token?appid="
                  << WeiXinAppID
                  << "&secret="
                  << WeiXinAppSecret
                  << "&code="
                  << response
                  << "&grant_type=authorization_code";
        request->setUrl( urlStream.str() );
        request->setRequestType(HttpRequest::Type::GET);
        
        request->setResponseCallback( CC_CALLBACK_2(WeiXinLogin::onHttpRequstCompleted, this) );
        
        HttpClient::getInstance()->sendImmediate(request);
        
        request->release();
    }
}

void WeiXinLogin::onHttpRequstCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response) {
        return;
    }
    
    // 你可以获取原始的请求类型 使用：response->request->reqType
    if (0 != strlen( response->getHttpRequest()->getTag() ) )
    {
        log("%s completed", response->getHttpRequest()->getTag() );
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "Http Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag() );
    log("%s", statusString);
    
    // 检查是否成功
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer() );
        return;
    }
    
    // dump data
    std::stringstream stringStream;
    std::vector<char> *buffer = response->getResponseData();
    log("weixin login, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        stringStream << (*buffer)[i];
    }
    std::cout << "dump data: " << stringStream.str() << std::endl;
    
    rapidjson::Document doc;
    doc.Parse(stringStream.str().c_str());
    
    if (doc.HasParseError()) {
        cout << "parse error: " << doc.GetParseError() << endl;
    }
    
    /*
     {"errcode":40029,"errmsg":"invalid code"}
     
     {
     "access_token":"ACCESS_TOKEN",
     "expires_in":7200,
     "refresh_token":"REFRESH_TOKEN",
     "openid":"OPENID",
     "scope":"SCOPE",
     "unionid":"o6_bmasdasdsad6_2sgVt7hMZOPfL"
     }
     */
    

    if (doc.IsObject() && doc.HasMember("errcode"))
    {
        int errcode;
        string errmsg = "";
        
        if ( doc.HasMember("errcode") && doc["errcode"].IsInt() ) {
            errcode = doc["errcode"].GetInt();
        }
        
        if ( doc.HasMember("errmsg") && doc["errmsg"].IsString() ) {
            errmsg = doc["errmsg"].GetString();
        }

        cout << "errcode: " << errcode << ", errmsg: " << errmsg << endl;
    }
    
    if (response->getHttpRequest()->getReferenceCount() != 2)
    {
        log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount() );
    }
}
