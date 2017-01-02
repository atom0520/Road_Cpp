#ifndef _START_LAYER_H_
#define _START_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class StartLayer :public Layer{
public:
	CREATE_FUNC(StartLayer);
	virtual bool init();
	virtual void onExit();
    
	Label * _exitLabel;
	EventListenerTouchOneByOne * _startGameListener;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	EventListenerKeyboard * _keyboardListener;
#endif
};

#endif