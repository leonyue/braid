//
//  Player.hpp
//  braid
//
//  Created by dj.yue on 2017/11/6.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

class Player : public cocos2d::Node{
    
public:
    virtual bool init() override;
    CREATE_FUNC(Player);
    void walkForward();
    void walkBackward();
    void halt();
private:
    cocos2d::Sprite *_sprite;
    void walk();
};

#endif /* Player_hpp */
