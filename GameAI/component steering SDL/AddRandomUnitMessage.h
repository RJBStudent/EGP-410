#pragma once

#include "GameMessage.h"

class AddRandomUnitMessage :public GameMessage
{
public:
	AddRandomUnitMessage();
	~AddRandomUnitMessage();

	void process();

private:
};