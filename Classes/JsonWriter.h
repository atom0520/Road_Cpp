#ifndef JSON_WRITER_H
#define JSON_WRITER_H

#include "cocos2d.h"
USING_NS_CC;

class JsonWriter : public Ref{
public:
	static JsonWriter * getInstance();
	static void destroyInstance();

	virtual bool init();
	void writeBeatNodeTouchTimeToFile();

protected:
	static  JsonWriter * _instance;

};

#endif