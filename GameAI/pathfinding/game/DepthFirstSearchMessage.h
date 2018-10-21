#pragma once
#include "GameMessage.h"

class DepthFirstSearchMessage :
	public GameMessage
{
public:
	DepthFirstSearchMessage();
	~DepthFirstSearchMessage();
	
	void process();
private:
};

