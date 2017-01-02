/*�����������ɡ����ü�ÿ�׸������������ ������*/
#ifndef _BEAT_NODE_MANAGER_H_
#define _BEAT_NODE_MANAGER_H_

#include "cocos2d.h"
#include "BeatNode.h"
USING_NS_CC;


	;
class BeatNodeManager : public Ref{
public:
	static  BeatNodeManager  * getInstance();
	static void destroyInstance();
	virtual bool init();
	void loadAllTracks();
	void update(float dt);
	BeatNode * getBeatNode(BeatNode::Type type);

	struct BeatNodeManagerBeat{
		int appearFrameIndex;
		int type;
	};
		
	struct Track{
		std::string name;
		std::vector<BeatNodeManagerBeat> beatList;
	};

	std::vector<BeatNode *> _beatNodes;
	std::map<int,Track> _tracks;

protected:
	static BeatNodeManager * _instance;
};

#endif