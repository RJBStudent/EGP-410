#pragma once

#include "GameMessage.h"

class IncreaseAlignmentWeightMessage :public GameMessage
{
public:
	IncreaseAlignmentWeightMessage();
	~IncreaseAlignmentWeightMessage();

	void process();

private:
};