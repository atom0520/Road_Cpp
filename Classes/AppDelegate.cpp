#include "AppDelegate.h"
#include "GameScene.h"
#include "StartScene.h"
#include "GlobalDefine.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace std;

//USING_NS_CC;
USING_NS_CC_EXT;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 736);
//static cocos2d::Size designResolutionSize = cocos2d::Size(640, 480);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {
	
}

AppDelegate::~AppDelegate() 
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
       // glview = GLViewImpl::createWithRect("BitBeat", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height),1.0,false);
		glview = GLViewImpl::createWithFullScreen("Road");

#else
        glview = GLViewImpl::create("Road");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
    
    //director->setAnimationInterval(1.0/100.0);
	if (BG_COLOR_TYPE){
		director->setClearColor(Color4F(255, 255, 255, 255));
	}
	

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    
    auto frameSize = glview->getFrameSize();
    
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {
        log("largeResolutionSize");
        //director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
        // set FPS. the default value is 1.0/60 if you don't call this
		framesPerSecond = 60.0;
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        log("mediumResolutionSize");
        //director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
		framesPerSecond = 100.0;
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        log("smallResolutionSize");
        //director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
		framesPerSecond = 100.0;
    }

	director->setAnimationInterval(1.0 / framesPerSecond);
    register_all_packages();

//    log("frameWidth is %f",frameSize.width);
//    log("frameHeight is %f",frameSize.height);
//    log("visibleWidth is %f",Director::getInstance()->getVisibleSize().width);
//    log("visibleHeight is %f",Director::getInstance()->getVisibleSize().height);
//    log("winWidth is %f",Director::getInstance()->getWinSize().width);
//    log("winHeight is %f",Director::getInstance()->getWinSize().height);
    
    //preload resource！！！
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC_FILENAME);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(ENDING_MUSIC_FILENAME);
	SimpleAudioEngine::getInstance()->preloadEffect(MUSIC_EFFECT_TAB_FILENAME);
	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("coffin.png")->getSpriteFrame(), "coffin");
	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("coffin_right_half.png")->getSpriteFrame(), "coffin_right_half");
	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("beat_line/beat_line_white.png")->getSpriteFrame(), "beat_line_white");
	SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create("beat_line/beat_line_grey.png")->getSpriteFrame(), "beat_line_grey");

	ArmatureDataManager::getInstance()->addArmatureFileInfo("BgAnimation/BgAnimation.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("BitBeatAnimation/BitBeatAnimation.ExportJson");

    // create a scene. it's an autorelease object
	//auto scene = GameScene::createScene();
	auto scene = StartScene::createScene();
    // run
    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

