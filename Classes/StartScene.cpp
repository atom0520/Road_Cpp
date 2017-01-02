#include "StartScene.h"
#include "StartLayer.h"

Scene * StartScene::createScene(){
	auto scene = Scene::create();
	
	auto startLayer = StartLayer::create();

	scene->addChild(startLayer, 1);
	return scene;
}