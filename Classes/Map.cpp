//
//  Map.cpp
//  braid
//
//  Created by dj.yue on 2017/11/6.
//
//

#include "Map.hpp"

using namespace cocos2d;

bool LevelMap::init() {
    if (! Layer::init()) {
        return false;
    }
    return true;
}

LevelMap *LevelMap::createMapByLevel(int level) {
    LevelMap *pRet = new(std::nothrow) LevelMap();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        TMXTiledMap *map  = TMXTiledMap::create("map/map.tmx");
        pRet->addChild(map);
        pRet->_map = map;
        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }

}