#include "GameScene.h"
#include "MapLayer.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "HudLayer.h"

#include "GameManager.h"
#include "MapManager.h"

#define FOR_TEST 1

Scene * GameScene::createScene(){
	auto gameScene = Scene::create();
	
	auto gameLayer = GameLayer::create();
	gameScene->addChild(gameLayer, 1);

	GameManager::getInstance()->_gameLayer = gameLayer;

	auto mapLayer = MapLayer::create();
	gameScene->addChild(mapLayer, 2);

	MapManager::getInstance()->_mapLayer = mapLayer;

	auto hudLayer = HudLayer::create();
	gameScene->addChild(hudLayer, 3);

	GameManager::getInstance()->_hudLayer = hudLayer;

	auto operateLayer = OperateLayer::create();
	gameScene->addChild(operateLayer, 4);

	auto testLabel1 = Label::create("", "", 20);
	GameManager::getInstance()->_testLabel1 = testLabel1;
	testLabel1->setAnchorPoint(Point(0, 0));
	testLabel1->setPosition(Point(16, 16));
	testLabel1->setTextColor(Color4B(0, 0, 0, 255));
	gameScene->addChild(testLabel1, 4);
	
	auto testLabel2 = Label::create("", "", 20);
	GameManager::getInstance()->_testLabel2 = testLabel2;
	testLabel2->setAnchorPoint(Point(0, 0));
	testLabel2->setPosition(Point(16, 16 + testLabel1->getContentSize().height + 16));
	testLabel2->setTextColor(Color4B(0, 0, 0, 255));
	gameScene->addChild(testLabel2, 4);


	return gameScene;
}