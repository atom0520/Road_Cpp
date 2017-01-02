#include "GameLayer.h"
#include "GameManager.h"
#include "MapManager.h"
#include "BeatNodeManager.h"
#include "GlobalDefine.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define forTest 1

bool GameLayer::init(){
	if (!Layer::init()){
		return false;
	}

	return true;
}

void GameLayer::onEnter()
{
	Layer::onEnter();
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()==true){
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
    log("game manager init update");
    MapManager::getInstance()->_mapLayer->m_backgroundAni();
    GameManager::getInstance()->_frameCounter = 0;
	this->schedule(schedule_selector(GameLayer::update), 1.0 / framesPerSecond);

	GameManager::getInstance()->_gameState = GameManager::GameState::INIT;
}

void GameLayer::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	GameManager::destroyInstance();
	MapManager::destroyInstance();
	BeatNodeManager::destroyInstance();
}

void GameLayer::update(float dt){
	GameManager::getInstance()->update(dt);
}

