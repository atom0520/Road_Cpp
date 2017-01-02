#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class HudLayer :public Layer{
public:
	CREATE_FUNC(HudLayer);
	virtual bool init();
	Label * _comboLabel;
};

#endif