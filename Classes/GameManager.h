#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
USING_NS_CC;

class BeatNode;
class HudLayer;
class GameManager : public Ref{
public:
	static GameManager * getInstance();
	static void destroyInstance();
	virtual bool init();
	void update(float dt);
	
	struct GameManagerWillAppearBeat{
		int appearFrameIndex;
		int type;
	};
	struct GameManagerWillTouchBeat{
		int touchFrameIndex;
		int type;
		bool checked;
		BeatNode * beatNode;
	};

	enum GameState{
		PAUSE = 0,
		INIT,
		ONGOING,
		ENDING
	};

	int _gameState;
	Layer * _gameLayer;
	HudLayer * _hudLayer;

	Label * _testLabel1;
	Label * _testLabel2;
	

	int _currentTrackId;

	std::vector<GameManagerWillAppearBeat> _willAppearBeatList;
	std::vector<GameManagerWillTouchBeat> _willTouchBeatList;

	void removeTouchBeatNode();
	void gameOver();

	int _comboNum;
	int _perfectNum;
	int _goodNum;
	int _missNum;
	int _missTouchNum;


	float _beatNodeSpeedPerSecond;
	float _beatNodeMoveTo1DestX;
	float _beatNodeMoveTo1Duration;
	float _beatNodeMoveTo2DestX;
	float _beatNodeMoveTo2Duration;
	float _beatNodeMoveTo3DestX;
	float _beatNodeMoveTo3Duration;

    int _frameCounter;
    std::string _beatNodeTouchTime;
protected:
	static float _updateCounter;
	static GameManager * _instance;
};

#endif