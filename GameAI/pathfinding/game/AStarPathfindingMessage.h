#pragma once
#include "GameMessage.h"

//Message class that changes the pathfinding type to A*
class AStarPathfindingMessage :
	public GameMessage
{
public:
	AStarPathfindingMessage();
	~AStarPathfindingMessage();

	void process();
};

