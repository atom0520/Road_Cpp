/*节奏点的类*/
#ifndef _BEAT_POINT_H_
#define _BEAT_POINT_H_

#include "GlobalDefine.h"
#include "cocos2d.h"
USING_NS_CC;

class BeatNode :public Sprite{
public:
	enum Type{
		UP=1,
		DOWN=2,
		LEFT=3,
		RIGHT=4,
	};
	

	CREATE_FUNC_WITH_ONE_PARAM(BeatNode, Type);
	virtual bool init(Type type);

	void hide();

protected:
	CC_SYNTHESIZE(Type, _type, Type);
};

#endif