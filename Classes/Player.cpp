//
//  Player.cpp
//  braid
//
//  Created by dj.yue on 2017/11/6.
//
//

#include "Player.hpp"

static const int kWalkTag = 12345;

using namespace cocos2d;

bool Player::init() {
    if (!Node::init()) {
        return false;
    }
    SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("player/player.plist");
    _sprite = cocos2d::Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("player_frame1.tiff"));
    addChild(_sprite);
    return true;
}

void Player::walk() {
    if (_sprite -> getActionByTag(kWalkTag) != NULL) {
        return;
    }
    Vector<SpriteFrame *> frames;
    SpriteFrameCache *frameCache=SpriteFrameCache::getInstance();
    char str[50] = {0};
    for (int i = 1; i < 9; i++) {
        sprintf(str, "player_frame%d.tiff",i);
        frames.pushBack(frameCache->getSpriteFrameByName(str));
    }
    
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(0.1f);
    auto anim = RepeatForever::create(Animate::create(animation));
    anim -> setTag(kWalkTag);
    _sprite->runAction(anim);
}

void Player::walkBackward() {
    _sprite->setFlippedX(true);
    walk();
}

void Player::walkForward() {
    _sprite->setFlippedX(false);
    walk();
}

void Player::halt() {
    _sprite->stopActionByTag(kWalkTag);
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("player_frame1.tiff");
    _sprite->setSpriteFrame(frame);
}