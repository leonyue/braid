//
//  Mario.hpp
//  braid-mobile
//
//  Created by dj.yue on 2017/11/7.
//

#ifndef Mario_hpp
#define Mario_hpp

#include <stdio.h>

class Mario : public cocos2d::Node{
    
public:
    virtual bool init() override;
    CREATE_FUNC(Mario);
    void walkForward();
    void walkBackward();
    void halt();
private:
    cocos2d::Sprite *_body;
    cocos2d::Sprite *_feet;
    void walk();
};

#endif /* Mario_hpp */
