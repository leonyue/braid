#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "JoyStick.hpp"

class JoyStick;
class Mario;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void joystickDirectionChangeCallBack(RDIRECTION direction);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    void updateUserLocation(float);
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void onContactSeparate(cocos2d::PhysicsContact &contact);
    Mario *_mario;
    cocos2d::TMXTiledMap *_map;
    JoyStick *_js;
};

#endif // __HELLOWORLD_SCENE_H__
