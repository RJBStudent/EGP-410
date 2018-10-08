#pragma once

#include "GameMessage.h"

class IncreaseCohesionWeightMessage :public GameMessage
{
public:
	IncreaseCohesionWeightMessage();
	~IncreaseCohesionWeightMessage();

	void process();

private:
};