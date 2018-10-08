#pragma once

#include "GameMessage.h"

class DecreaseSeperationWeightMessage :public GameMessage
{
public:
	DecreaseSeperationWeightMessage();
	~DecreaseSeperationWeightMessage();

	void process();

private:
};