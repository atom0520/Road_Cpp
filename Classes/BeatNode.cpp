#include "BeatNode.h"

bool BeatNode::init(Type type){

	if (!Sprite::init()){
		return false;
	}
	this->_type = type;
	//switch (type){
	//case UP:
	//	this->setTexture("beat_nodes/beat_node_up.png");
	//	break;
	//case DOWN:
	//	this->setTexture("beat_nodes/beat_node_down.png");
	//	break;
	//case LEFT:
	//	this->setTexture("beat_nodes/beat_node_left.png");
	//	break;
	//case RIGHT:
	//	this->setTexture("beat_nodes/beat_node_right.png");
	//	break;
	//}

	this->setTexture("beat_nodes/beat_node_elec.png");

	this->setVisible(true);
	
	return true;
}

void BeatNode::hide(){

	auto fadeTo = FadeTo::create(0.2, 0);

	auto fadeOutSequence = Sequence::create(fadeTo, CallFunc::create([&](){this->setVisible(false); this->setOpacity(255); }), nullptr);

	//this->setVisible(false);
	this->runAction(fadeOutSequence);
	
}