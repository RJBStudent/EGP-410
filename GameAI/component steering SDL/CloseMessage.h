#pragma once

#include "GameMessage.h"

class CloseMessage :public GameMessage
{
public:
	CloseMessage();
	~CloseMessage();

	void process();

private:
};