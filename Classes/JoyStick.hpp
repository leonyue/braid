//
//  JoyStick.hpp
//  braid
//
//  Created by dj.yue on 2017/11/3.
//
//

#ifndef JoyStick_hpp
#define JoyStick_hpp

#include <stdio.h>

typedef enum direction
{
    STAY = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    R_UP, //右上
    R_DOWN,
    L_UP,
    L_DOWN
    
}RDIRECTION;

typedef  std::function<void(RDIRECTION)> lyJoystickCallback;

class JoyStick : public cocos2d::Layer {
    
public:
    virtual bool init() override;
    CREATE_FUNC(JoyStick);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void setCallback(const lyJoystickCallback& callback);

    RDIRECTION _dir;
private:
    cocos2d::EventListenerTouchOneByOne *listener;
    cocos2d::Sprite *joystick;
    cocos2d::Sprite *joystick_bg;
    void checkDirection(float angle);
    lyJoystickCallback _callback;
    
};

#endif /* JoyStick_hpp */
