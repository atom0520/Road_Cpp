#include"StartLayer.h"
#include "GameScene.h"

bool StartLayer::init(){
	auto bg1 = Sprite::create("start_scene/start_background_1.png");
	bg1->setAnchorPoint(Point(0.5, 1));
	bg1->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height));
	
	auto bg2 = Sprite::create("start_scene/start_background_2.png");
	bg2->setAnchorPoint(Point(0.5, 1));
	bg2->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height));

	this->addChild(bg2, 1);
	this->addChild(bg1, 2);

	auto logo = Sprite::create("start_scene/start_logo.png");
	logo->setAnchorPoint(Point(0.5, 0.5));
	logo->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(logo, 3);

	auto pressHint = Sprite::create("start_scene/start_button.png");
	pressHint->setAnchorPoint(Point(0.5, 0.5));
	pressHint->setPosition(Point(Director::getInstance()->getWinSize().width / 2, logo->getPositionY() - logo->getContentSize().height / 2 - pressHint->getContentSize().height / 2));
	this->addChild(pressHint, 4);

	auto fadeSequence = Sequence::create(FadeTo::create(1.0, 255), FadeTo::create(1.0, 32),nullptr);
	pressHint->runAction(RepeatForever::create(fadeSequence));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event){
		auto newScene = GameScene::createScene();
		auto transition = TransitionFade::create(1.5, newScene);
		Director::getInstance()->replaceScene(transition);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
#endif
    _startGameListener = EventListenerTouchOneByOne::create();
	_startGameListener->setSwallowTouches(true);
	_startGameListener->onTouchBegan = [&](Touch* touch, Event* event)
	{

		return true;
	};
	_startGameListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        auto newScene = GameScene::createScene();
        auto transition = TransitionFade::create(1.5, newScene);
        Director::getInstance()->replaceScene(transition);
        
        //return true;
    };
    
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_startGameListener, this);
    
	_exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 48);
	_exitLabel->setAnchorPoint(Point(1.0, 0.0));
	_exitLabel->setPosition(Point(Director::getInstance()->getWinSize().width-12, 8));
	_exitLabel->setTextColor(Color4B(128, 128, 128, 222));
	this->addChild(_exitLabel, 5);
	
	auto exitListener = EventListenerTouchOneByOne::create();
	exitListener->setSwallowTouches(true);
	exitListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		if (_exitLabel->getBoundingBox().containsPoint(touch->getLocation())){
			//MessageBox("begin touch exit label", "test");
			return true;
		}
		else{
			return false;
		}
	};

	exitListener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		//MessageBox("end touch exit label", "test");
		if (_exitLabel->getBoundingBox().containsPoint(touch->getLocation())){
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	};
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exitListener, _exitLabel);
	return true;
}

void StartLayer::onExit(){
	Layer::onExit();

	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(_exitLabel);
}