//
//  Map.hpp
//  braid
//
//  Created by dj.yue on 2017/11/6.
//
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>

class LevelMap : cocos2d::Layer {
    
public:
    virtual bool init() override;
    static LevelMap *createMapByLevel(int level);
private:
    cocos2d::TMXTiledMap *_map;
};

#endif /* Map_hpp */
