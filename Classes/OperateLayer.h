/*游戏主场景的操作层 场景类*/
#ifndef _OPERATE_LAYER_H_
#define _OPERATE_LAYER_H_


#include "cocos2d.h"
USING_NS_CC;

class OperateLayer :public Layer{
public:
	CREATE_FUNC(OperateLayer);
	virtual bool init();
	virtual void onExit();
	void OnClickScreen(int actualTouchFrameIndexFrameIndex, int dueTouchBeatIndex);

};

#endif