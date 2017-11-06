//
//  JoyStick.cpp
//  braid
//
//  Created by dj.yue on 2017/11/3.
//
//

#include "JoyStick.hpp"

USING_NS_CC;

bool JoyStick::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    joystick_bg = Sprite::create("joystick-bg.png");
    joystick_bg->setPosition(Vec2(100,120));
    addChild(joystick_bg);
    
    joystick = Sprite::create("joystick.png");
    joystick->setPosition(Vec2(100,120));
    addChild(joystick);
    
    return true;
}

void JoyStick::onEnter() {
    Layer::onEnter();
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void JoyStick::onExit() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    float radius = joystick_bg->getContentSize().width / 2;
    Vec2 center = joystick_bg->getPosition();
    Vec2 touch_pos = touch->getLocation();
    
    if (touch->getLocation().distance(center) > radius) {
        return false;
    } else {
        joystick->setPosition(touch_pos);
        float angle = acosf((touch_pos.x - center.x) / touch_pos.distance(center));
        if (touch_pos.y > center.y) {
            checkDirection(angle);
        } else {
            checkDirection(-angle);
        }
        return true;
    }
    
}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    float radius = joystick_bg->getContentSize().width / 2;
    Vec2 center = joystick_bg->getPosition();
    
    Vec2 target_pos,touch_pos;
    touch_pos = touch->getLocation();
    target_pos = touch_pos;
    
    float angle = acosf((touch_pos.x - center.x) / touch_pos.distance(center));
    if (target_pos.distance(center) > radius) {
        if ( touch_pos.y >  center.y ) {
            target_pos = Vec2(center.x + radius * cosf(angle), center.y + radius * sinf(angle));
            
        }
        else {
            target_pos = Vec2(center.x + radius * cosf(angle), center.y - radius * sinf(angle));
        }
        
    }
    
    if (target_pos.y > center.y) {
        checkDirection(angle);
    } else {
        checkDirection(-angle);
    }

    joystick->setPosition(target_pos);
}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 center = joystick_bg->getPosition();
    
    _dir = STAY;
    if (_callback) {
        _callback(_dir);
    }
    joystick->setPosition(center);
}

#pragma mark - public

void JoyStick::setCallback(const lyJoystickCallback &callback) {
    _callback = callback;
}

#pragma mark - private

void JoyStick::checkDirection(float angle) {
    RDIRECTION dir;
    if (angle >= -M_PI/8.0 && angle <= M_PI/8.0) {
        dir = RIGHT;
    }
    if (angle >= -(M_PI/8.0) && angle <= M_PI/8.0) {
        dir = RIGHT;
    }
    else if( angle >= M_PI/8.0 && angle < 3*M_PI/8.0) {
        dir = R_UP;
    }
    else if( angle >= 3*M_PI/8.0 && angle <= 5*M_PI/8.0) {
        dir = UP;
    }
    else if( angle > 5*M_PI/8.0 && angle < 7*M_PI/8.0) {
        dir = L_UP;
    }
    else if( (angle >= 7*M_PI/8.0 && angle <= M_PI) || (angle <= -7*M_PI/8.0 && angle >= -M_PI)){
        dir = LEFT;
    }
    else if( angle > -7*M_PI/8.0 && angle < -5*M_PI/8.0) {
        dir = L_DOWN;
    }
    else if( angle >= -5*M_PI/8.0 && angle <= -3*M_PI/8.0) {
        dir = DOWN;
    }
    else if( angle > -3*M_PI/8.0 && angle < -M_PI/8.0 ) {
        dir = R_DOWN;
    }
    
    if (dir != _dir) {
        _dir = dir;
        if (_callback) {
            _callback(_dir);
        }
    }
    
}