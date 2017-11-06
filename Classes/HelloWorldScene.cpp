#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "JoyStick.hpp"
#include "Player.hpp"

USING_NS_CC;

static const float kMoveSpeed = 30;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress.  it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    // add a test man
//    auto man = Sprite::create("joystick.png");
    auto man = Player::create();
    man->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    addChild(man);
    _man = man;
    
    // add JoyStick
    JoyStick *js = JoyStick::create();
    js->setPosition(Vec2::ZERO);
    js->setCallback(CC_CALLBACK_1(HelloWorld::joystickDirectionChangeCallBack, this));
    addChild(js);
    _js = js;
    
    // add schedule
//    this->schedule(schedule_selector(HelloWorld::updateUserLocation), 0.1, 1, 0);
    
    return true;
}


void HelloWorld::updateUserLocation(float dt) {
//    RDIRECTION dir = _js->_dir;
//    switch (dir) {
//        case UP:
//            auto Mov
//            break;
//            
//        default:
//            break;
//    }
}

void HelloWorld::joystickDirectionChangeCallBack(RDIRECTION direction) {
    _man->stopAllActions();
    Vec2 by;
    switch (direction) {
        case STAY:
            _man->halt();
            break;
        case RIGHT:
            by = Vec2(kMoveSpeed, 0);
            _man->walkForward();
            break;
        case LEFT:
            by = Vec2(-kMoveSpeed, 0);
            _man->walkBackward();
            break;
        case UP:
            by = Vec2(0, kMoveSpeed);
            break;
        case DOWN:
            by = Vec2(0, -kMoveSpeed);
            break;
        default:
            break;
    }
    if (by.x == 0 && by.y == 0) {
        return;
    }
    
    RepeatForever *moveRepeat = RepeatForever::create(MoveBy::create(1.f, by));
    _man->runAction(moveRepeat);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
