//
//  LoadingScene.hpp
//  braid-mobile
//
//  Created by dj.yue on 2017/11/8.
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <stdio.h>

class LoadingScene : public cocos2d::Scene {
    
public:
    virtual bool init();
    virtual void onEnter() override;
    
    CREATE_FUNC(LoadingScene);
    
private:
    void preloadResource();
    void loadingCallback(cocos2d::Texture2D*);
};

#endif /* LoadingScene_hpp */
