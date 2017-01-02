#include "MapManager.h"
#include "GameManager.h"
#include "AnimationManager.h"
#include "GlobalDefine.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
MapManager *  MapManager::_instance = nullptr;

MapManager * MapManager::getInstance(){
	if (_instance == nullptr){
		_instance = new MapManager();
		_instance->init();
	}

	return _instance;
}

bool MapManager::init(){
	
	
	return true;
}

void MapManager::destroyInstance(){
	if (!_instance){
		return;
	}

	delete _instance;
	_instance = nullptr;
}

void MapManager::setMap(){
	auto winSize = Director::getInstance()->getWinSize();
	auto child = Sprite::create();
	
	child->setAnchorPoint(Point(0.5, 0.5));
	child->setPosition(Point(HERO_MAP_POS_X, CHILD_HERO_MAP_POS_Y));
	
	child->setScale(0.5, 0.5);
	auto animate = Animate::create(AnimationManager::getInstance()->_animations["child_walk"]);
	child->runAction(RepeatForever::create(animate));
	
	_mapLayer->addChild(child, HERO_MAP_LAYER_Z_ORDER);

	_hero = child;

	MapManager::getInstance()->_hero = child;

	auto beatLineWhite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("beat_line_white"));
	beatLineWhite->setAnchorPoint(Point(0.0, 0.5));
	auto scale1 = Director::getInstance()->getWinSize().width / beatLineWhite->getContentSize().width;
	beatLineWhite->setScale(scale1);
	beatLineWhite->setPosition(Point(0, CHILD_HEART_MAP_POS_Y));
	_beatLineWhite = beatLineWhite;

	_mapLayer->addChild(beatLineWhite, BEAT_LINE_WHITE_MAP_LAYER_Z_ORDER);

	auto beatLineGrey = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("beat_line_grey"));
	
	beatLineGrey->setAnchorPoint(Point(0.0, 0.5));
	auto scale2 = Director::getInstance()->getWinSize().width / beatLineGrey->getContentSize().width;
	beatLineWhite->setScale(scale2);
	beatLineGrey->setPosition(Point(0, CHILD_HEART_MAP_POS_Y));
	_beatLineGrey = beatLineGrey;

	_mapLayer->addChild(beatLineGrey, BEAT_LINE_GREY_MAP_LAYER_Z_ORDER);

	auto heart = Sprite::create();
	heart->setScale(0.75, 0.75);
	heart->setAnchorPoint(Point(0.5, 0.5));
	heart->setPosition(Point(HEART_MAP_POS_X, CHILD_HEART_MAP_POS_Y));
	
	auto heartAnimate = Animate::create(AnimationManager::getInstance()->_animations["heart_loop"]);
	heart->runAction(RepeatForever::create(heartAnimate));
	_heart = heart;

	_mapLayer->addChild(heart, HEART_MAP_LAYER_Z_ORDER);
	
}