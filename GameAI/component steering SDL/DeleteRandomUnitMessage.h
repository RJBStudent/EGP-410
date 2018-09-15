#pragma once

#include "GameMessage.h"

class DeleteRandomUnitMessage :public GameMessage
{
public:
	DeleteRandomUnitMessage();
	~DeleteRandomUnitMessage();

	void process();

private:
};