#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "JoyStick.hpp"
#include "Player.hpp"
#include "Mario.hpp"
#include "Map.hpp"

USING_NS_CC;

static const float kMoveSpeed = 100;
static const float KTunnelTag = 101;
static const float kBrownBlockTag = 102;
static const int   kMarioTag = 0x09;

Scene* HelloWorld::createScene()
{
    Scene *scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-100));
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
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
    
    
    //add bg
    LayerColor *colorLayer = LayerColor::create(Color4B(244, 234, 234, 244));
    addChild(colorLayer, -4);
    
    //add map
    TMXTiledMap *map = TMXTiledMap::create("map/level1.tmx");
    map->setAnchorPoint(Vec2(0, 0));
    map->setPosition(Vec2(origin.x, origin.y));
    addChild(map, 10, 666);
    _map = map;
    
    auto group = map->getObjectGroup("ObjectLayer1");
    auto objects = group->getObjects();
    for (auto obj : objects) {
        ValueMap &dict = obj.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        std::string type = dict["type"].asString();
        if (type.compare("Block") == 0) {
            CCLOG("it is a block:");
        }
        
        PhysicsBody *phy = PhysicsBody::createBox(Size(width, height));
        phy->setDynamic(false);
        phy->getFirstShape()->setDensity(1.0);
        phy->getFirstShape()->setFriction(1.f);
        phy->getFirstShape()->setRestitution(0.f);
        phy->getFirstShape()->setContactTestBitmask(0x00001);
        Sprite *sp = Sprite::create();
        sp->setPosition(Vec2(x,y));
        sp->setAnchorPoint(Vec2::ZERO);
        sp->setContentSize(Size(width, height));
        sp->setPhysicsBody(phy);
        _map->addChild(sp);
    }
    
    
    // add mario
    auto mario = Mario::create();
    mario->setPosition(origin.x + visibleSize.width / 2, origin.y + 10 );
    mario->setPhysicsBody(PhysicsBody::createBox(mario->getContentSize()));
    mario->setTag(kMarioTag);
    mario->getPhysicsBody()->setRotationEnable(false);
    mario->getPhysicsBody()->getFirstShape()->setDensity(1.f);
    mario->getPhysicsBody()->getFirstShape()->setRestitution(0.f);
    mario->getPhysicsBody()->getFirstShape()->setFriction(1.f);
    mario->getPhysicsBody()->getFirstShape()->setContactTestBitmask(0x00001);
    addChild(mario);
    _mario = mario;
    
//    auto follow = Follow::create(mario);
//    runAction(follow);
    
    // add JoyStick
    JoyStick *js = JoyStick::create();
    js->setPosition(Vec2::ZERO);
    js->setCallback(CC_CALLBACK_1(HelloWorld::joystickDirectionChangeCallBack, this));
    addChild(js);
    _js = js;
    
    this->schedule(schedule_selector(HelloWorld::updateUserLocation), 0.1, CC_REPEAT_FOREVER, 0);
    
    // add map
    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeShape = Node::create();
    edgeShape->setPhysicsBody(body);
    edgeShape->setPosition(origin.x +visibleSize.width / 2,origin.y + visibleSize.height/2);
    addChild(edgeShape);
    
    return true;
}

void HelloWorld::onEnter() {
    Scene::onEnter();
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool HelloWorld::onContactBegin(PhysicsContact &contact) {
    auto a = contact.getShapeA()->getBody()->getNode();
    auto b = contact.getShapeB()->getBody()->getNode();
    Node *mario = nullptr;
    Node *another = nullptr;
    if (a->getTag() == kMarioTag) {
        mario = a;
        another = b;
    }
    if (b->getTag() == kMarioTag) {
        mario = b;
        another = b;
    }
    
    if (mario != nullptr) {
        mario->stopActionByTag(199);
        Rect rect =  mario->getBoundingBox().unionWithRect(another->getBoundingBox());
    }
    
    return true;
}

void HelloWorld::onContactSeparate(cocos2d::PhysicsContact &contact) {
    
}
void HelloWorld::updateUserLocation(float dt) {
    switch (_js->_dir) {
        case STAY:
            break;
        case RIGHT:
        {
            auto move = MoveBy::create(dt, Vec2(-kMoveSpeed * dt, 0));
            move->setTag(199);
            _map->runAction(move);
        }
            break;
        case LEFT:
        {
            auto move = MoveBy::create(dt, Vec2(kMoveSpeed * dt, 0));
            move->setTag(199);
            _map->runAction(move);
        }
            break;
        case UP:
            break;
        case DOWN:
            break;
        default:
            break;
    }
}

void HelloWorld::joystickDirectionChangeCallBack(RDIRECTION direction) {
    switch (direction) {
        case STAY:
            _mario->halt();
            break;
        case RIGHT:
            _mario->walkForward();
            break;
        case LEFT:
            _mario->walkBackward();
            break;
        case UP:
//            _mario->getPhysicsBody()->applyImpulse(Vec2(0,20000.f));
            break;
        case DOWN:
            break;
        default:
            break;
    }
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
