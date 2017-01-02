/*动画的管理类*/
#ifndef _ANIMATION_MANAGER_H
#define _ANIMATION_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

/*
动画类型

帧动画
动作动画？
*/

//游戏动画管理类
class AnimationManager : public Ref{
public:
	static AnimationManager * getInstance();
	static void destroyInstance();

	virtual bool init();

	void loadAllAnimations();

	std::map<std::string, Animation*> _animations;



protected:
	static AnimationManager * _instance;
	
	
};

#endif