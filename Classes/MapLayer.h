
#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
using namespace cocostudio;

using namespace std;


USING_NS_CC;
USING_NS_CC_EXT;

class MapLayer :public Layer{
public:

	CREATE_FUNC(MapLayer);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void m_backgroundAni();
	void BgActorAni1();
	void BgActorAni2();
	void BgActorAni3();
	void BgActorAni4();
	void BgActorAni5();
	void BgActorAni6();
	void BgActorAni7();
	void BgActorAni8();
	void BgActorAni9();
	void BgActorAni10();
	void BgActorAni11();
	void BgActorAni12();
	void BgActorAni13();
	void BgActorAni14();
	void BgActorAni15();
	void BgActorAni16();
	void BgActorAni17();
	void BgActorAni18();
	void BgActorAni19();

	std::map<int, Armature*> _bgArmatures;
};

#endif