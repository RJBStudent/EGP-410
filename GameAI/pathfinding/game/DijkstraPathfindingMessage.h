#pragma once
#include "GameMessage.h"

//Message class that changes the pathfinding type to Dijkstra.
class DijkstraPathfindingMessage :
	public GameMessage
{
public:
	DijkstraPathfindingMessage();
	~DijkstraPathfindingMessage();

	void process();
};

