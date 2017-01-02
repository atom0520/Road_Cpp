#include "BeatNodeManager.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace rapidjson;

//ÉùÃ÷¾²Ì¬±äÁ¿
BeatNodeManager *  BeatNodeManager::_instance = nullptr;

BeatNodeManager * BeatNodeManager::getInstance(){
	if (_instance == nullptr){
		_instance = new BeatNodeManager();
		_instance->init();
	}
	return _instance;
}

bool BeatNodeManager::init(){
	
	loadAllTracks();
	return true;
}

void BeatNodeManager::destroyInstance(){
	if (!_instance){
		return;
	}
	
	for (auto it = _instance->_beatNodes.begin(); it < _instance->_beatNodes.end();){
		if ((*it) != nullptr){
			(*it)->removeFromParentAndCleanup(true);
			it = _instance->_beatNodes.erase(it);
		}
		else{
			it++;
		}
	}	

	for (auto it = _instance->_tracks.begin(); it != _instance->_tracks.end();){
		it = _instance->_tracks.erase(it);
	}

	delete _instance;
	_instance = nullptr;
}

void BeatNodeManager::loadAllTracks(){
	
	rapidjson::Document readDoc;
	auto load_str = FileUtils::getInstance()->getStringFromFile("tracks/track.json");
	readDoc.Parse<rapidjson::kParseDefaultFlags>(load_str.c_str());

	if (readDoc.HasParseError()){
		return;
	}
	if (!readDoc.IsObject())
		return;

	//for (int i = 1;; i++){
		//auto indexStr = String::createWithFormat("track_%02d", i)->getCString();

		if (!readDoc.HasMember("tracks")){
			return;
		}
		rapidjson::Value& trackArray = readDoc["tracks"];
		

		for (int i = 0; i<trackArray.Size(); i++){

			//std::string trackName = trackdoc["name"].GetString();
			rapidjson::Value &  trackData = trackArray[i];
			std::string  trackName = trackData["track"].GetString();
			std::string  beatNodesStr = trackData["nodes"].GetString();
			String * beatNodesCCStr = String::create(beatNodesStr);
			auto beatNodesData = beatNodesCCStr->componentsSeparatedByString(",");

			Track track = Track{ trackName };

			for (int j = 0; j < beatNodesData->count(); j++){

				auto beatNodeCCStr = (String*)beatNodesData->getObjectAtIndex(j);

				//String * beatNodeCCStr = String::create(beatNodeStr);
				auto beatNodeData = beatNodeCCStr->componentsSeparatedByString("-");
				auto beatNodeTimeStr = (String*)beatNodeData->getObjectAtIndex(0);
				//int beatNodeFrame = (int)(beatNodeFrameStr->uintValue()/100.0*60.0);
				int beatNodeFrame = beatNodeTimeStr->uintValue()*(framesPerSecond/100.0) - SECOND_BETWEEN_BEAT_APPEAR_AND_TOUCH*framesPerSecond;
				
				auto beatNodeTypeStr = (String*)beatNodeData->getObjectAtIndex(1);
				int beatNodeType = beatNodeTypeStr->uintValue();

				BeatNodeManagerBeat beat = BeatNodeManagerBeat{ beatNodeFrame, beatNodeType };

				//track.beatList.push_back(std::pair<int, int>(beatNodeFrame, beatNodeType));
				track.beatList.push_back(beat);
			}
			this->_tracks[i] = track;

			//auto textCCStr = String::createWithFormat("trackName is %s", this->_tracks[i].name.c_str());
			//MessageBox(textCCStr->getCString(), "test");
		}
	//}
	

}

void BeatNodeManager::update(float dt){
	
}

BeatNode * BeatNodeManager::getBeatNode(BeatNode::Type type){
	for (int i = 0; i < _beatNodes.size(); i++){
		if (_beatNodes[i] != nullptr){
			if (_beatNodes[i]->getType() == type && _beatNodes[i]->isVisible() == false){
				_beatNodes[i]->setVisible(true);
				return _beatNodes[i];
			}
		}
	}
	auto newBeatNode = BeatNode::create(type);
	_beatNodes.push_back(newBeatNode);

	return newBeatNode;
}