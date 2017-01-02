/*�����Ĺ�����*/
#ifndef _ANIMATION_MANAGER_H
#define _ANIMATION_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

/*
��������

֡����
����������
*/

//��Ϸ����������
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