//
//  Mario.cpp
//  braid-mobile
//
//  Created by dj.yue on 2017/11/7.
//

#include "Mario.hpp"

static const int kWalkTag = 12345;

using namespace cocos2d;

bool Mario::init() {
    if (!Node::init()) {
        return false;
    }
    _body = Sprite::create("mario/mariok.png");
    this->setContentSize(_body->getContentSize());
    _body->setPosition(_body->getContentSize().width/ 2,_body->getContentSize().height / 2);
    addChild(_body);
    SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("mario/runningfeet.plist");
    
    _feet = cocos2d::Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("foot1.png"));
    _feet->setPosition(0.f, 0.f);
    _feet->setAnchorPoint(Vec2(0, 0));
    _feet->setFlippedX(true);
    _feet->setVisible(false);
    _body->addChild(_feet);
    return true;
}

void Mario::walk() {
    if (_feet -> getActionByTag(kWalkTag) != NULL) {
        return;
    }
    _body -> setTexture("mario/mario.png");
    _feet -> setVisible(true);
    Vector<SpriteFrame *> frames;
    SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
    char str[50] = {0};
    for (int i = 1; i < 5; i++) {
        sprintf(str, "foot%d.png",i);
        frames.pushBack(frameCache->getSpriteFrameByName(str));
    }
    
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(0.05f);
    auto anim = RepeatForever::create(Animate::create(animation));
    anim -> setTag(kWalkTag);
    _feet->runAction(anim);
}

void Mario::walkBackward() {
    _body->setFlippedX(true);
    _feet->setFlippedX(false);
    walk();
}

void Mario::walkForward() {
    _body->setFlippedX(false);
    _feet->setFlippedX(true);
    walk();
}

void Mario::halt() {
    _feet->stopActionByTag(kWalkTag);
    _feet->setVisible(false);
    _body->setTexture("mario/mariok.png");
//    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("foot1.png");
//    _feet->setSpriteFrame(frame);
}
