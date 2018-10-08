#pragma once

#include "GameMessage.h"

class DecreaseCohesionWeightMessage :public GameMessage
{
public:
	DecreaseCohesionWeightMessage();
	~DecreaseCohesionWeightMessage();

	void process();

private:
};