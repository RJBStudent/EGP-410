#pragma once

#include "GameMessage.h"

class DecreaseAlignmentWeightMessage :public GameMessage
{
public:
	DecreaseAlignmentWeightMessage();
	~DecreaseAlignmentWeightMessage();

	void process();

private:
};