#include "HudLayer.h"

bool HudLayer::init(){
	if (!Layer::init()){
		return false;
	}

    _comboLabel = Label::createWithTTF("Combo:", "fonts/arial.ttf", 48);
    
    _comboLabel->setAnchorPoint(Point(0.0,1.0));

	_comboLabel->setPosition(Point(12, Director::getInstance()->getWinSize().height - 8));
	_comboLabel->setTextColor(Color4B(8, 8, 8, 255));
	
	this->addChild(_comboLabel, 1);

	return true;
}