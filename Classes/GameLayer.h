/*��Ϸ���������߼��� ������
��update��Ϊ��ѭ�����
*/
#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class GameLayer :public Layer{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();

	//void updateTimeCounter(float dt);
	virtual void onEnter();
	virtual void onExit();
	void update(float dt);
protected:

};

#endif