#include "AnimationManager.h"

//ÉùÃ÷¾²Ì¬±äÁ¿
AnimationManager * AnimationManager::_instance = nullptr;

AnimationManager * AnimationManager::getInstance(){
	if (_instance == nullptr){
		_instance = new AnimationManager();
		_instance->init();
	}
	return _instance;
}

void AnimationManager::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool AnimationManager::init(){
	loadAllAnimations();
	return true;
}

void AnimationManager::loadAllAnimations(){
	auto animationCache = AnimationCache::getInstance();
	animationCache->addAnimationsWithFile("animations/child_animations.plist");
	animationCache->addAnimationsWithFile("animations/teen_animations.plist");
	animationCache->addAnimationsWithFile("animations/adult_animations.plist");
	animationCache->addAnimationsWithFile("animations/old_animations.plist");

	animationCache->addAnimationsWithFile("animations/heart_animations.plist");

	_animations["child_walk"] = animationCache->getAnimation("child_walk");
	_animations["teen_walk"] = animationCache->getAnimation("teen_walk");
	_animations["adult_walk"] = animationCache->getAnimation("adult_walk");
	_animations["old_walk"] = animationCache->getAnimation("old_walk");

	_animations["heart_loop"] = animationCache->getAnimation("heart_loop");
	_animations["heart_hit_1"] = animationCache->getAnimation("heart_hit_1");
	_animations["heart_hit_2"] = animationCache->getAnimation("heart_hit_2");
	//_animations["hero_good"] = animationCache->getAnimation("hero_good");
	//_animations["hero_perfect"] = animationCache->getAnimation("hero_perfect");
	//_animations["hero_miss"] = animationCache->getAnimation("hero_miss");
}
