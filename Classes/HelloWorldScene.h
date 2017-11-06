#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "JoyStick.hpp"

class JoyStick;
class Player;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void joystickDirectionChangeCallBack(RDIRECTION direction);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    void updateUserLocation(float);
    Player *_man;
    JoyStick *_js;
};

#endif // __HELLOWORLD_SCENE_H__
