//
//  LoadingScene.cpp
//  braid-mobile
//
//  Created by dj.yue on 2017/11/8.
//

#include "LoadingScene.hpp"
#include "cocos2d.h"

using namespace cocos2d;
bool LoadingScene::init() {
    if (!Scene::init()) {
        return false;
    }
    this->preloadResource();
    return true;
}

void LoadingScene::onEnter() {
    Scene::onEnter();
    auto label = Label::create();
}

void LoadingScene::preloadResource() {
    std::string resourceMain = "resources/";
    Director::getInstance()->getTextureCache()->addImageAsync(resourceMain + "mariocloud1.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
}

void LoadingScene::loadingCallback(Texture2D *texutrue)
{
    CCLOG("texutre:%p loaded",texutrue);
}
