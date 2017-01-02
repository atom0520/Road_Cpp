#include "MapLayer.h"
#include "MapManager.h"

bool MapLayer::init(){
	if (!Layer::init()){
		return false;
	}
	_bgArmatures[0] = Armature::create("BgAnimation");
	_bgArmatures[0]->setPosition(Vec2(0, 0));
	this->addChild(_bgArmatures[0], 0);

	_bgArmatures[1] = Armature::create("BitBeatAnimation");
	_bgArmatures[1]->setPosition(Vec2(1100, 100));
	this->addChild(_bgArmatures[1], 1);
	_bgArmatures[1]->setScale(0.4f);

	_bgArmatures[2] = Armature::create("BitBeatAnimation");
	_bgArmatures[2]->setPosition(Vec2(1100, 300));
	this->addChild(_bgArmatures[2], 2);
	_bgArmatures[2]->setScale(0.4f);

	_bgArmatures[3] = Armature::create("BitBeatAnimation");
	_bgArmatures[3]->setPosition(Vec2(1100, 500));
	this->addChild(_bgArmatures[3], 3);
	_bgArmatures[3]->setScale(0.4f);

	_bgArmatures[4] = Armature::create("BitBeatAnimation");
	_bgArmatures[4]->setPosition(Vec2(1100, 50));
	_bgArmatures[4]->setScale(0.8f);
	this->addChild(_bgArmatures[4], 4);

	_bgArmatures[5] = Armature::create("BitBeatAnimation");
	_bgArmatures[5]->setPosition(Vec2(1100, 100));
	_bgArmatures[5]->setScale(0.8f);
	this->addChild(_bgArmatures[5], 5);

	_bgArmatures[6] = Armature::create("BitBeatAnimation");
	_bgArmatures[6]->setPosition(Vec2(1100, 200));
	_bgArmatures[6]->setScale(0.8f);
	this->addChild(_bgArmatures[6], 6);

	_bgArmatures[7] = Armature::create("BitBeatAnimation");
	_bgArmatures[7]->setPosition(Vec2(1100, 300));
	_bgArmatures[7]->setScale(0.4f);
	this->addChild(_bgArmatures[7], 7);

	_bgArmatures[8] = Armature::create("BitBeatAnimation");
	_bgArmatures[8]->setPosition(Vec2(1100, 400));
	_bgArmatures[8]->setScale(0.4f);
	this->addChild(_bgArmatures[8], 8);

	_bgArmatures[9] = Armature::create("BitBeatAnimation");
	_bgArmatures[9]->setPosition(Vec2(1100, 500));
	_bgArmatures[9]->setScale(0.4f);
	this->addChild(_bgArmatures[9], 9);

	_bgArmatures[10] = Armature::create("BitBeatAnimation");
	_bgArmatures[10]->setPosition(Vec2(1100, 600));
	_bgArmatures[10]->setScale(0.4f);
	this->addChild(_bgArmatures[10],10);

	_bgArmatures[11] = Armature::create("BitBeatAnimation");
	_bgArmatures[11]->setPosition(Vec2(1100, 200));
	_bgArmatures[11]->setScale(0.4f);
	this->addChild(_bgArmatures[11], 11);

	_bgArmatures[12] = Armature::create("BitBeatAnimation");
	_bgArmatures[12]->setPosition(Vec2(1100, 400));
	_bgArmatures[12]->setScale(0.4f);
	this->addChild(_bgArmatures[12], 12);

	_bgArmatures[13] = Armature::create("BitBeatAnimation");
	_bgArmatures[13]->setPosition(Vec2(1100, 600));
	_bgArmatures[13]->setScale(0.4f);
	this->addChild(_bgArmatures[13], 13);

	_bgArmatures[14] = Armature::create("BitBeatAnimation");
	_bgArmatures[14]->setPosition(Vec2(1100, 100));
	_bgArmatures[14]->setScale(0.4f);
	this->addChild(_bgArmatures[14], 14);

	_bgArmatures[15] = Armature::create("BitBeatAnimation");
	_bgArmatures[15]->setPosition(Vec2(1100, 200));
	_bgArmatures[15]->setScale(0.4f);
	this->addChild(_bgArmatures[15], 15);

	_bgArmatures[16] = Armature::create("BitBeatAnimation");
	_bgArmatures[16]->setPosition(Vec2(1100, 300));
	_bgArmatures[16]->setScale(0.4f);
	this->addChild(_bgArmatures[16], 16);

	_bgArmatures[17] = Armature::create("BitBeatAnimation");
	_bgArmatures[17]->setPosition(Vec2(1100, 400));
	_bgArmatures[17]->setScale(0.4f);
	this->addChild(_bgArmatures[17], 17);

	_bgArmatures[18] = Armature::create("BitBeatAnimation");
	_bgArmatures[18]->setPosition(Vec2(1100, 500));
	_bgArmatures[18]->setScale(0.4f);
	this->addChild(_bgArmatures[18], 18);

	_bgArmatures[19] = Armature::create("BitBeatAnimation");
	_bgArmatures[19]->setPosition(Vec2(1100, 600));
	_bgArmatures[19]->setScale(0.4f);
	this->addChild(_bgArmatures[19], 19);

	return true;
}

void MapLayer::onEnter(){
	Layer::onEnter();
	
}

void MapLayer::onExit(){
	Layer::onExit();
	for (auto it = _bgArmatures.begin(); it != _bgArmatures.end();){
		it = _bgArmatures.erase(it);
	}
}

void MapLayer::m_backgroundAni()
{
	_bgArmatures[0]->getAnimation()->play("Animation1");
	
}

void MapLayer::BgActorAni1()
{
	_bgArmatures[1]->getAnimation()->play("YoungRoseAni");
}

void MapLayer::BgActorAni2()
{
	_bgArmatures[2]->getAnimation()->play("YoungHeartAni");
}

void MapLayer::BgActorAni3()
{
	_bgArmatures[3]->getAnimation()->play("YoungHeartSwordAni");
}

void MapLayer::BgActorAni4()
{
	_bgArmatures[4]->getAnimation()->play("ChildStar3Ani");
}

void MapLayer::BgActorAni5()
{
	_bgArmatures[5]->getAnimation()->play("ChildStar2Ani");
}

void MapLayer::BgActorAni6()
{
	_bgArmatures[6]->getAnimation()->play("ChildStar1Ani");
}

void MapLayer::BgActorAni7()
{
	_bgArmatures[7]->getAnimation()->play("ChildJokerAni");
}

void MapLayer::BgActorAni8()
{
	_bgArmatures[8]->getAnimation()->play("ChildDuckAni");
}

void MapLayer::BgActorAni9()
{
	_bgArmatures[9]->getAnimation()->play("ChildBabyAni");
}

void MapLayer::BgActorAni10()
{
	_bgArmatures[10]->getAnimation()->play("ChildBearAni");
}

void MapLayer::BgActorAni11()
{
	_bgArmatures[11]->getAnimation()->play("MidLifeMaskAni");
}

void MapLayer::BgActorAni12()
{
	_bgArmatures[12]->getAnimation()->play("MidLifeBabyAni");
}

void MapLayer::BgActorAni13()
{
	_bgArmatures[13]->getAnimation()->play("MidLifeWatchAni");
}
void MapLayer::BgActorAni14()
{
	_bgArmatures[14]->getAnimation()->play("OldCrowFly");
}
void MapLayer::BgActorAni15()
{
	_bgArmatures[15]->getAnimation()->play("OldCrowStand");
}
void MapLayer::BgActorAni16()
{
	_bgArmatures[16]->getAnimation()->play("OldBellAni");
}
void MapLayer::BgActorAni17()
{
	_bgArmatures[17]->getAnimation()->play("OldFeather1Ani");
}
void MapLayer::BgActorAni18()
{
	_bgArmatures[18]->getAnimation()->play("OldFeather2Ani");
}
void MapLayer::BgActorAni19()
{
	_bgArmatures[19]->getAnimation()->play("OldFeather3Ani");
}




