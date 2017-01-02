#include "OperateLayer.h"
#include "BeatNode.h"
#include "MapManager.h"
#include "GameManager.h"
#include "GameManager.h"
#include "AnimationManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool OperateLayer::init(){
	if (!Layer::init()){
		return false;
	}
    
//	auto missMark = Sprite::create("arrow.png");
//	missMark->setPosition(Point(GameManager::getInstance()->_beatNodeMoveTo2DestX, Director::getInstance()->getWinSize().height / 2));
//	this->addChild(missMark, 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event){
		
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE){
			if (GameManager::getInstance()->_gameState != GameManager::GameState::ONGOING){
				return;
			}
			log("touch frame is %d", GameManager::getInstance()->_frameCounter);
			GameManager::getInstance()->_beatNodeTouchTime.append(String::createWithFormat("%ld-1,", GameManager::getInstance()->_frameCounter)->getCString());
			if (!GameManager::getInstance()->_willTouchBeatList.empty()){
				OnClickScreen(GameManager::getInstance()->_frameCounter, 0);
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
#endif

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [&](Touch* touch, Event* event)
	{	
		if (GameManager::getInstance()->_gameState != GameManager::GameState::ONGOING){
			return false;
		}

		if (!GameManager::getInstance()->_willTouchBeatList.empty()){
			OnClickScreen(GameManager::getInstance()->_frameCounter, 0);
		}
		
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();
	return true;
}

void OperateLayer::onExit(){
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}
void OperateLayer::OnClickScreen(int actualTouchFrameIndex,int dueTouchBeatIndex)
{ 
	
	int _checkValue = GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].touchFrameIndex - actualTouchFrameIndex;
	if (abs(_checkValue) > CHECK_FRAME_RANGE){
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect(MUSIC_EFFECT_TAB_FILENAME);

	if (abs(_checkValue) <= PERFECT_CHECK_FRAME_RANGE){
		log("peferct");
		
		auto heartLight = Sprite::create("heart_effect/effect_perfect.png");
		heartLight->setPosition(Point(HEART_MAP_POS_X, CHILD_HEART_MAP_POS_Y));
		heartLight->setScale(0.75);
		heartLight->setOpacity(0);
		auto heartLightFadeAnimate = Sequence::create(FadeTo::create(0.15, 128), FadeTo::create(0.15, 0), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, heartLight)), nullptr);
		MapManager::getInstance()->_mapLayer->addChild(heartLight, 6);
		heartLight->runAction(heartLightFadeAnimate);

		GameManager::getInstance()->_comboNum += 1;
		GameManager::getInstance()->_perfectNum += 1;

		auto hitAnimate2 = Animate::create(AnimationManager::getInstance()->_animations["heart_hit_2"]);
		auto loopAnimate = Animate::create(AnimationManager::getInstance()->_animations["heart_loop"]);
		auto perfectSequence = Sequence::create(hitAnimate2, RepeatForever::create(loopAnimate), nullptr);

		//MapManager::getInstance()->_heart->stopAllActions();
		MapManager::getInstance()->_heart->runAction(perfectSequence);

		
		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].checked = true;
		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].beatNode->stopAllActions();
		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].beatNode->hide();
		GameManager::getInstance()->_willTouchBeatList.erase(GameManager::getInstance()->_willTouchBeatList.begin() + dueTouchBeatIndex);
		
	}
	else if (abs(_checkValue) <= GOOD_CHECK_FRAME_RANGE){
		log("good");
		
		auto heartLight = Sprite::create("heart_effect/effect_good.png");
		heartLight->setPosition(Point(HEART_MAP_POS_X, CHILD_HEART_MAP_POS_Y));
		heartLight->setOpacity(0);
		heartLight->setScale(0.75);
		auto heartLightFadeAnimate = Sequence::create(FadeTo::create(0.15, 128), FadeTo::create(0.15, 0), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, heartLight)), nullptr);
		MapManager::getInstance()->_mapLayer->addChild(heartLight, 6);
		heartLight->runAction(heartLightFadeAnimate);

		GameManager::getInstance()->_comboNum += 1;
		GameManager::getInstance()->_goodNum += 1;

		auto hitAnimate1 = Animate::create(AnimationManager::getInstance()->_animations["heart_hit_1"]);
		auto loopAnimate = Animate::create(AnimationManager::getInstance()->_animations["heart_loop"]);
		auto goodSequence = Sequence::create(hitAnimate1, RepeatForever::create(loopAnimate), nullptr);
		//MapManager::getInstance()->_heart->stopAllActions();
		MapManager::getInstance()->_heart->runAction(goodSequence);

		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].checked = true;
		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].beatNode->stopAllActions();
		GameManager::getInstance()->_willTouchBeatList[dueTouchBeatIndex].beatNode->hide();
		GameManager::getInstance()->_willTouchBeatList.erase(GameManager::getInstance()->_willTouchBeatList.begin() + dueTouchBeatIndex);
	}
	else{
		log("miss");
		
		auto heartLight = Sprite::create("heart_effect/effect_miss.png");
		heartLight->setPosition(Point(HEART_MAP_POS_X, CHILD_HEART_MAP_POS_Y));
		heartLight->setOpacity(0);
		auto heartLightFadeAnimate = Sequence::create(FadeTo::create(0.15, 222), FadeTo::create(0.15, 0), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, heartLight)), nullptr);
		MapManager::getInstance()->_mapLayer->addChild(heartLight, 10);
		heartLight->runAction(heartLightFadeAnimate);

		/*auto flashLayer = LayerColor::create();
		if (BG_COLOR_TYPE){
			flashLayer->initWithColor(Color4B(0, 0, 0, 128), Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
		}
		else{
			flashLayer->initWithColor(Color4B(255, 255, 255, 128), Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
		}
		auto fadeAnimate = Sequence::create(FadeTo::create(0.5, FLASH_LAYER_OPACITY), FadeTo::create(0.5, 0),CallFunc::create(CC_CALLBACK_0(Layer::removeFromParent,flashLayer)), nullptr);
		MapManager::getInstance()->_mapLayer->addChild(flashLayer, 10);

		flashLayer->stopAllActions();
		flashLayer->runAction(fadeAnimate);*/

		GameManager::getInstance()->_comboNum = 0;
		GameManager::getInstance()->_missNum += 1;
		GameManager::getInstance()->_missTouchNum += 1;
		
		GameManager::getInstance()->_willTouchBeatList.erase(GameManager::getInstance()->_willTouchBeatList.begin() + dueTouchBeatIndex);

	}
		
}

