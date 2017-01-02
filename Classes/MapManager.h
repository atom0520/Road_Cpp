#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

#include "cocos2d.h"
#include "MapLayer.h"
USING_NS_CC;

class PhysicsSprite;

class MapManager : public Ref{
public:
	static MapManager * getInstance();
	static void destroyInstance();
	virtual bool init();

	MapLayer * _mapLayer;
	Layer * _beatNodeLayer;

	Sprite * _hero;
	Sprite * _heart;

	int _mapWidth;
	int _mapHeight;

	void setMap();
	
	Sprite *_beatLineWhite;
	Sprite *_beatLineGrey;

protected:
	static MapManager * _instance;
};

#endif