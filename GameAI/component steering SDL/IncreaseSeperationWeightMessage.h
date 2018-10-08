#pragma once

#include "GameMessage.h"

class IncreaseSeperationWeightMessage :public GameMessage
{
public:
	IncreaseSeperationWeightMessage();
	~IncreaseSeperationWeightMessage();

	void process();

private:
};