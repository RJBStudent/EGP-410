#pragma once
#include "GameMessage.h"
class DijkstraPathfindingMessage :
	public GameMessage
{
public:
	DijkstraPathfindingMessage();
	~DijkstraPathfindingMessage();

	void process();
};

