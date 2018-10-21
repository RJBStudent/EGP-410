#pragma once
#include "GameMessage.h"
class AStarPathfindingMessage :
	public GameMessage
{
public:
	AStarPathfindingMessage();
	~AStarPathfindingMessage();

	void process();
};

