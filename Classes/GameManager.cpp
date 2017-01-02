#include "GameManager.h"
#include "BeatNode.h"
#include "HudLayer.h"

#include "MapManager.h"
#include "BeatNodeManager.h"
#include "AnimationManager.h"
#include "StartScene.h"

#include "SimpleAudioEngine.h"
#include "JsonWriter.h"
using namespace CocosDenshion;

GameManager *  GameManager::_instance = nullptr;

GameManager * GameManager::getInstance(){
	if (_instance == nullptr){
		_instance = new GameManager();
		_instance->init();
	}
	return _instance;
}

bool GameManager::init(){
	_gameState = PAUSE;

	float beatNodeWidth = BeatNode::create(BeatNode::Type::UP)->getContentSize().width;
	_beatNodeSpeedPerSecond = (Director::getInstance()->getWinSize().width + beatNodeWidth / 2.0 - HEART_MAP_POS_X) / SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH;
	
	_beatNodeMoveTo1DestX = HEART_MAP_POS_X;
	_beatNodeMoveTo1Duration = SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH;
	_beatNodeMoveTo2Duration = MISS_CHECK_FRAME_RANGE / framesPerSecond;
	_beatNodeMoveTo2DestX = HEART_MAP_POS_X - _beatNodeMoveTo2Duration * _beatNodeSpeedPerSecond;
	_beatNodeMoveTo3DestX = -beatNodeWidth / 2.0;
	_beatNodeMoveTo3Duration = (_beatNodeMoveTo2DestX - _beatNodeMoveTo3DestX) / _beatNodeSpeedPerSecond;

	_comboNum=0;
	_perfectNum=0;
	_goodNum=0;
	_missNum=0;

	_missTouchNum = 0;
    _frameCounter = 0;
    _beatNodeTouchTime = std::string("");

	return true;
}

void GameManager::destroyInstance(){
	if (!_instance){
		return;
	}
	for (auto it = _instance->_willAppearBeatList.begin(); it < _instance->_willAppearBeatList.end();)
	{
		it = _instance->_willAppearBeatList.erase(it);
	}
	for (auto it = _instance->_willTouchBeatList.begin(); it < _instance->_willTouchBeatList.end();)
	{
		it = _instance->_willTouchBeatList.erase(it);
	}

	delete _instance;
	_instance = nullptr;
}

void GameManager::update(float dt){
	//log("update dt is %f", dt);
	switch (_gameState){
	case PAUSE:
		break;
	case INIT:{
        _frameCounter += 1;
        
        if(_frameCounter == 1){
            MapManager::getInstance()->setMap();
            
            _willAppearBeatList.clear();
            _currentTrackId = 0;
            for (int i = 0; i < BeatNodeManager::getInstance()->_tracks[_currentTrackId].beatList.size(); i++){
                GameManagerWillAppearBeat beat = GameManagerWillAppearBeat{
                    BeatNodeManager::getInstance()->_tracks[_currentTrackId].beatList[i].appearFrameIndex,
                    BeatNodeManager::getInstance()->_tracks[_currentTrackId].beatList[i].type };
                _willAppearBeatList.push_back(beat);
            }
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC_FILENAME);
           /* int delay;
            for(delay=0;delay<10000;delay++){
                
            }*/
        }
        
		do{
			if (MapManager::getInstance()->_mapLayer->_bgArmatures[0]->getAnimation()->isPlaying()){
				//log("_frameCounter threshold is %f", 2.0*framesPerSecond);
				//log("_frameCounter is %d", _frameCounter);
				if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() != true){
					SimpleAudioEngine::getInstance()->stopBackgroundMusic();
					SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC_FILENAME, false);
				}

				if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == true){
					_frameCounter = 0;
					_gameState = ONGOING;
					break;
				}
			}
		} while (1);
        /*if(_frameCounter > 2.0*framesPerSecond){
            
        }*/

		break;
	}
		
	case ONGOING:{

        _frameCounter += 1;

        if (_frameCounter == HERO_TRANSFORM_1_FRAME_INDEX ||
            _frameCounter == HERO_TRANSFORM_2_FRAME_INDEX ||
            _frameCounter == HERO_TRANSFORM_3_FRAME_INDEX){
            
            auto oldHero = MapManager::getInstance()->_hero;
            
            auto heroFadeOutSequence = Sequence::create(FadeTo::create(1.0, 0), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, oldHero)), nullptr);
            oldHero->runAction(heroFadeOutSequence);
            
            auto oldHeart = MapManager::getInstance()->_heart;
            auto heartFadeOutSequence = Sequence::create(FadeTo::create(1.0, 0), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, oldHeart)), nullptr);
            oldHeart->runAction(heartFadeOutSequence);
            
            auto newHero = Sprite::create();
            newHero->setAnchorPoint(Point(0.5, 0.5));
            if (_frameCounter == HERO_TRANSFORM_1_FRAME_INDEX){
                newHero->setPosition(Point(HERO_MAP_POS_X, TEEN_HERO_MAP_POS_Y));
            }
            else if (_frameCounter == HERO_TRANSFORM_2_FRAME_INDEX){
                newHero->setPosition(Point(HEART_MAP_POS_X, ADULT_HERO_MAP_POS_Y));
            }
            else if (_frameCounter == HERO_TRANSFORM_3_FRAME_INDEX){
                newHero->setPosition(Point(HEART_MAP_POS_X, OLD_HERO_MAP_POS_Y));
            }
            //newHero->setPosition(Point(HERO_MAP_POS_X, CHILD_HERO_MAP_POS_Y));
            newHero->setScale(0.5, 0.5);
            newHero->setOpacity(0);
            
            if (_frameCounter == HERO_TRANSFORM_1_FRAME_INDEX){
                auto animate = Animate::create(AnimationManager::getInstance()->_animations["teen_walk"]);
                newHero->runAction(RepeatForever::create(animate));
            }
            else if (_frameCounter == HERO_TRANSFORM_2_FRAME_INDEX){
                auto animate = Animate::create(AnimationManager::getInstance()->_animations["adult_walk"]);
                newHero->runAction(RepeatForever::create(animate));
            }
            else if (_frameCounter == HERO_TRANSFORM_3_FRAME_INDEX){
                auto animate = Animate::create(AnimationManager::getInstance()->_animations["old_walk"]);
                newHero->runAction(RepeatForever::create(animate));
            }
            
            auto heroFadeInSequence = Sequence::create(FadeTo::create(1.0, 255), nullptr);
            newHero->runAction(heroFadeInSequence);
            MapManager::getInstance()->_mapLayer->addChild(newHero,HERO_MAP_LAYER_Z_ORDER);
            MapManager::getInstance()->_hero = newHero;
            
            auto newHeart = Sprite::create();
            newHeart->setScale(0.75, 0.75);
            newHeart->setAnchorPoint(Point(0.5, 0.5));
            
            if (_frameCounter == HERO_TRANSFORM_1_FRAME_INDEX){
                newHeart->setPosition(Point(HEART_MAP_POS_X, TEEN_HEART_MAP_POS_Y));
            }
            else if (_frameCounter == HERO_TRANSFORM_2_FRAME_INDEX){
                newHeart->setPosition(Point(HEART_MAP_POS_X, ADULT_HEART_MAP_POS_Y));
            }
            else if (_frameCounter == HERO_TRANSFORM_3_FRAME_INDEX){
                newHeart->setPosition(Point(HEART_MAP_POS_X, OLD_HEART_MAP_POS_Y));
            }
            
            newHeart->setOpacity(0);
            
            auto heartAnimate = Animate::create(AnimationManager::getInstance()->_animations["heart_loop"]);
            newHeart->runAction(RepeatForever::create(heartAnimate));
            auto heartFadeInSequence = Sequence::create(FadeTo::create(1.0, 255), nullptr);
            newHeart->runAction(heartFadeInSequence);
            
            MapManager::getInstance()->_mapLayer->addChild(newHeart, HEART_MAP_LAYER_Z_ORDER);
            MapManager::getInstance()->_heart = newHeart;
            
        }
        else if (_frameCounter == (1.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni4();

			MapManager::getInstance()->_mapLayer->BgActorAni10();

		}
		else if (_frameCounter == (10.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni6();
			MapManager::getInstance()->_mapLayer->BgActorAni7();
			MapManager::getInstance()->_mapLayer->BgActorAni8();
		}
		else if (_frameCounter == (20.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni9();
			MapManager::getInstance()->_mapLayer->BgActorAni5();
		}
		else if (_frameCounter == (38.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni1();
		}
		else if (_frameCounter == (48.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni2();
		}
		else if (_frameCounter == (60.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni3();
		}
		else if (_frameCounter == (76.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni12();
		}
		else if (_frameCounter == (86.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni11();
		}
		else if (_frameCounter == (95.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni13();
		}
		else if (_frameCounter == (116.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni4();
			MapManager::getInstance()->_mapLayer->BgActorAni9();
		}
		else if (_frameCounter == (128.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni7();
			MapManager::getInstance()->_mapLayer->BgActorAni8();
		}
		else if (_frameCounter == (139.0)*framesPerSecond){
			MapManager::getInstance()->_mapLayer->BgActorAni5();
			MapManager::getInstance()->_mapLayer->BgActorAni6();
		}
        else if (_frameCounter == ENTER_ENDING_FRAME_INDEX){
			
			JsonWriter::getInstance()->writeBeatNodeTouchTimeToFile();

			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			//hide map objects
		
			MapManager::getInstance()->_beatLineWhite->runAction(
				Sequence::create(
				FadeTo::create(0.5, 0),
				CallFunc::create([&](){MapManager::getInstance()->_beatLineWhite->setVisible(false); }),
				nullptr));

			MapManager::getInstance()->_beatLineGrey->runAction(
				Sequence::create(
				FadeTo::create(0.5, 0),
				CallFunc::create([&](){MapManager::getInstance()->_beatLineGrey->setVisible(false); }),
				nullptr));

			MapManager::getInstance()->_heart->runAction(
				Sequence::create(
				FadeTo::create(0.5, 0),
				CallFunc::create([&](){MapManager::getInstance()->_heart->setVisible(false); }),
				nullptr));

			//coffin arise
			auto coffin = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("coffin"));
			auto coffinMask = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("coffin_right_half"));
            
			coffinMask->setAnchorPoint(Point(1.0, 0.5));
			//coffin->setAnchorPoint(Point(0.5, 0.5));
            coffin->setScale(2.0);
            coffinMask->setScale(2.0);
            
			coffin->setPosition(Point(Director::getInstance()->getWinSize().width + coffin->getContentSize().width / 2*coffin->getScaleX(), COFFIN_MAP_POS_Y));
			coffinMask->setPosition(Point(coffin->getPositionX() + coffin->getContentSize().width/2*coffin->getScaleX(), coffin->getPositionY()));
			
			MapManager::getInstance()->_mapLayer->addChild(coffin, COFFIN_MAP_LAYER_Z_ORDER);
			MapManager::getInstance()->_mapLayer->addChild(coffinMask, COFFIN_MASK_LAYER_Z_ORDER);
			
			//coffin&hero actions
			float coffinFinalScale =
            MIN(Director::getInstance()->getWinSize().width / (coffin->getContentSize().width),
                Director::getInstance()->getWinSize().height / (coffin->getContentSize().height) );
            
			auto coffinSequence = Sequence::create(
				MoveTo::create(8.0, Point(Director::getInstance()->getWinSize().width*3 / 4, coffin->getPositionY())),
				CallFunc::create([&](){
				MapManager::getInstance()->_hero->setVisible(false); 
				
			}),
				DelayTime::create(1.0),
				Spawn::create(MoveTo::create(4.0, Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2)),
				ScaleTo::create(4.0, coffinFinalScale), nullptr),
			DelayTime::create(1.0),
			CallFunc::create(CC_CALLBACK_0(GameManager::gameOver, this)),
			nullptr);

			auto coffinMaskSequence = Sequence::create(
				MoveTo::create(8.0, Point(Director::getInstance()->getWinSize().width * 3 / 4 + coffin->getContentSize().width/2*coffin->getScaleX(), coffin->getPositionY())),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, coffinMask)),
				nullptr);

			auto heroSequence = Sequence::create(
				MoveTo::create(4.0,Point(Director::getInstance()->getWinSize().width / 2, OLD_HERO_MAP_POS_Y)), nullptr);

			coffin->runAction(coffinSequence);
			coffinMask->runAction(coffinMaskSequence);
			MapManager::getInstance()->_hero->runAction(heroSequence);

			_gameState = GameState::ENDING;

		}
		
		/*For HUD*/
		auto comboLabelStr = String::createWithFormat("Combo:%d", _comboNum);
        //std::string comboLabelStr = StringUtils::format("Combo:%d", _comboNum);
        
        _hudLayer->_comboLabel->setString(comboLabelStr->getCString());

		/*test*/
		if (!_willTouchBeatList.empty()){
			int i;
			for (i = 0; i < _willTouchBeatList.size(); i++){
				if (_willTouchBeatList[i].checked == false){
					break;
				}
			}
			if (i < _willTouchBeatList.size()){
				auto testLabel1Str = String::createWithFormat("next dueTouchBeat touchFrameIndex is %d", _willTouchBeatList[i].touchFrameIndex);
				_testLabel1->setString(testLabel1Str->getCString());
			}
			
	    }
		/*if (!_willAppearBeatList.empty()){
			auto testLabel1Str = String::createWithFormat("_willAppearBeatList[0].first is %d", _willAppearBeatList[0].appearFrameIndex);
			_testLabel1->setString(testLabel1Str->getCString());
		}*/

		auto testLabel2Str = String::createWithFormat("current musicFrameCounter is %ld", _frameCounter);
		//auto testLabel2Str = String::createWithFormat("current musicTimeCounterInMillisecond is %ld", TimeManager::getInstance()->getCurrentTimeInMillisecond() - TimeManager::getInstance()->_startMusicTimeInMillisecond);
		_testLabel2->setString(testLabel2Str->getCString());
		
		if (!_willAppearBeatList.empty()){
			if (_willAppearBeatList[0].appearFrameIndex == _frameCounter){

				auto beatNode = BeatNodeManager::getInstance()->getBeatNode((BeatNode::Type)_willAppearBeatList[0].type);
				
				if (beatNode->getParent() == nullptr){
					MapManager::getInstance()->_mapLayer->addChild(beatNode, BEAT_NODE_MAP_LAYER_Z_ORDER);
				}

				float beatNodePosY;
				if (_frameCounter < HERO_TRANSFORM_1_FRAME_INDEX - SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH*framesPerSecond){
					beatNodePosY =  CHILD_HEART_MAP_POS_Y;
				}
				else if (_frameCounter < HERO_TRANSFORM_2_FRAME_INDEX - SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH*framesPerSecond){
					beatNodePosY = TEEN_HEART_MAP_POS_Y;
				}
				else if (_frameCounter < HERO_TRANSFORM_3_FRAME_INDEX - SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH*framesPerSecond){
					beatNodePosY = ADULT_HEART_MAP_POS_Y;
				}
				else{
					beatNodePosY = OLD_HEART_MAP_POS_Y;
				}
				beatNode->setPosition(Point(Director::getInstance()->getWinSize().width + beatNode->getContentSize().width / 2, beatNodePosY));

				auto moveTo1 = MoveTo::create(_beatNodeMoveTo1Duration, Point(_beatNodeMoveTo1DestX, beatNodePosY));
				auto moveTo2 = MoveTo::create(_beatNodeMoveTo2Duration, Point(_beatNodeMoveTo2DestX, beatNodePosY));
				auto moveTo3 = MoveTo::create(_beatNodeMoveTo3Duration, Point(_beatNodeMoveTo3DestX, beatNodePosY));
				
				auto sequence = Sequence::create(
					moveTo1,
					moveTo2,
					moveTo3, 
					CallFunc::create(CC_CALLBACK_0(BeatNode::hide, beatNode)),		
					 nullptr);

				beatNode->runAction(sequence);


				GameManagerWillTouchBeat willTouchBeat = GameManagerWillTouchBeat{
					(int)(_willAppearBeatList[0].appearFrameIndex + SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH*framesPerSecond),
					_willAppearBeatList[0].type,
					false,
					beatNode };

				_willTouchBeatList.push_back(willTouchBeat);
				_willAppearBeatList.erase(_willAppearBeatList.begin());
			}
	   }
       if (!_willTouchBeatList.empty()){
			int i;
			for (i = 0; i < _willTouchBeatList.size(); i++){
				if (_willTouchBeatList[i].checked == true){
					continue;
				}
				if (_frameCounter == _willTouchBeatList[i].touchFrameIndex + MISS_CHECK_FRAME_RANGE){
	
					_comboNum = 0;
					_missNum += 1;
					
					_willTouchBeatList.erase(_willTouchBeatList.begin() + i);
					break;
				}
				else if (_frameCounter < _willTouchBeatList[i].touchFrameIndex + MISS_CHECK_FRAME_RANGE){
					break;
				}
			
			}
		}

		break;
	}
	case ENDING:{
		break;
	}
	}
	
}

void GameManager::gameOver(){
	SimpleAudioEngine::getInstance()->playBackgroundMusic(ENDING_MUSIC_FILENAME,true);
	auto memberListSprite = Sprite::create("member_list.png");
	memberListSprite->setScale(1.5);
	memberListSprite->setColor(Color3B(255, 255, 255));

	MapManager::getInstance()->_mapLayer->addChild(memberListSprite, MEMBER_LIST_MAP_LAYER_Z_ORDER);
	memberListSprite->setAnchorPoint(Point(0.5, 1.0));
	memberListSprite->setPosition(Director::getInstance()->getWinSize().width / 2, 0);
	memberListSprite->runAction(
		Sequence::create(
		MoveTo::create(20.0, Point(memberListSprite->getPositionX(), Director::getInstance()->getWinSize().height + memberListSprite->getContentSize().height*memberListSprite->getScaleY())),
		DelayTime::create(1.5f),
		CallFunc::create([&](){
            auto endingLabel = Label::create("---The End---", "", 88);
            
            endingLabel->setOpacity(0);
            endingLabel->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
            MapManager::getInstance()->_mapLayer->addChild(endingLabel, ENDING_LABEL_MAP_LAYER_Z_ORDER);
            
            endingLabel->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.0, 255), FadeTo::create(2.0, 32), nullptr)));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            auto endKeyboardListener = EventListenerKeyboard::create();
            endKeyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event){
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                auto newScene = StartScene::createScene();
                auto transition = TransitionFade::create(1.5, newScene);
                Director::getInstance()->replaceScene(transition);
            };
            
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(endKeyboardListener, GameManager::getInstance()->_gameLayer);
#endif
            auto endTouchListener = EventListenerTouchOneByOne::create();
            endTouchListener->onTouchBegan = [&](Touch* touch, Event* event){
                SimpleAudioEngine::getInstance()->stopBackgroundMusic();
                auto newScene = StartScene::createScene();
                auto transition = TransitionFade::create(1.5, newScene);
                Director::getInstance()->replaceScene(transition);
                return true;
            };
            
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(endTouchListener, GameManager::getInstance()->_gameLayer);
        }),
		nullptr));
    
	memberListSprite->runAction(RepeatForever::create(Sequence::create(FadeTo::create(2.0, 255), FadeTo::create(2.0, 128), nullptr)));
}