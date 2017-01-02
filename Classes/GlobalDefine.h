/*全局共用宏的声明文件*/

#define CREATE_FUNC_WITH_ONE_PARAM(__TYPE__,paramType1)\
public: static __TYPE__* create(paramType1 param1)\
{\
	__TYPE__ * pRet = new __TYPE__();\
	if (pRet && pRet->init(param1))\
				{\
		pRet->autorelease();\
		return pRet;\
				}\
								else\
							    {\
		delete pRet;\
		pRet = nullptr;\
		return nullptr;\
								}\
}

#define SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH 3.0
#define CHECK_FRAME_RANGE 20.0
#define PERFECT_CHECK_FRAME_RANGE 5.0
#define GOOD_CHECK_FRAME_RANGE 10.0
#define MISS_CHECK_FRAME_RANGE 15.0

#define FLASH_LAYER_OPACITY 64

#define HERO_MAP_POS_X  (HEART_MAP_POS_X - 8)
#define CHILD_HERO_MAP_POS_Y (Director::getInstance()->getWinSize().height/2-24)
#define TEEN_HERO_MAP_POS_Y (Director::getInstance()->getWinSize().height/2-80)
#define ADULT_HERO_MAP_POS_Y (Director::getInstance()->getWinSize().height/2-64)
#define OLD_HERO_MAP_POS_Y (Director::getInstance()->getWinSize().height/2-64)

#define COFFIN_MAP_POS_Y (OLD_HERO_MAP_POS_Y+400)

#define HEART_MAP_POS_X (Director::getInstance()->getWinSize().width / 4 )
#define CHILD_HEART_MAP_POS_Y (Director::getInstance()->getWinSize().height/2 )
#define TEEN_HEART_MAP_POS_Y (Director::getInstance()->getWinSize().height/2 )
#define ADULT_HEART_MAP_POS_Y (Director::getInstance()->getWinSize().height/2 )
#define OLD_HEART_MAP_POS_Y (Director::getInstance()->getWinSize().height/2 )

#define BEAT_LINE_WHITE_MAP_LAYER_Z_ORDER 1
#define BEAT_LINE_GREY_MAP_LAYER_Z_ORDER 2
#define BEAT_NODE_MAP_LAYER_Z_ORDER 7
#define HERO_MAP_LAYER_Z_ORDER 5
#define HEART_MAP_LAYER_Z_ORDER 6
#define COFFIN_MAP_LAYER_Z_ORDER 3
#define COFFIN_MASK_LAYER_Z_ORDER HERO_MAP_LAYER_Z_ORDER+1
#define MEMBER_LIST_MAP_LAYER_Z_ORDER 10
#define ENDING_LABEL_MAP_LAYER_Z_ORDER 12

#define HERO_TRANSFORM_1_FRAME_INDEX 37*framesPerSecond
#define HERO_TRANSFORM_2_FRAME_INDEX 75*framesPerSecond
#define HERO_TRANSFORM_3_FRAME_INDEX 115*framesPerSecond
#define ENTER_ENDING_FRAME_INDEX 158*framesPerSecond

#define BEAT_NODE_MAP_POS_Y (Director::getInstance()->getWinSize().height/2 + 64)

#define BG_MUSIC_FILENAME "sounds/bg_music.mp3"
#define ENDING_MUSIC_FILENAME "sounds/ending_music_pure.wav"
#define MUSIC_EFFECT_TAB_FILENAME "sounds/tab.wav"

#define BG_COLOR_TYPE 0

extern int framesPerSecond;