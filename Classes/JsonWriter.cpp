#include "JsonWriter.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

#include "GameManager.h"

JsonWriter * JsonWriter::_instance = nullptr;

JsonWriter * JsonWriter::getInstance(){
	if (_instance == nullptr){
		_instance = new JsonWriter();
		_instance->init();
	}
	return _instance;
}

void JsonWriter::destroyInstance(){
	if (!_instance){
		return;
	}
	delete _instance;
	_instance = nullptr;
}

bool  JsonWriter::init(){

	return true;
}

void JsonWriter::writeBeatNodeTouchTimeToFile(){

	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	
	//rapidjson::Value tracks(rapidjson::kObjectType);
	
	rapidjson::Value array(rapidjson::kArrayType);

	rapidjson::Value object(rapidjson::kObjectType);

	object.AddMember("track", "bitbeat1", allocator);
	object.AddMember("nodes", rapidjson::Value(GameManager::getInstance()->_beatNodeTouchTime.c_str(), allocator), allocator);
	
	array.PushBack(object, allocator);

	writedoc.AddMember("tracks", array, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("track.json");
    
    log("track file has been saved to %s",path.c_str());
    
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());

}