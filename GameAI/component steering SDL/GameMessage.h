#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	KEYBOARD_MESSAGE = 1,
	MOUSE_MESSAGE = 2,
	PLAYER_ARRIVE_AND_SEEK = 3,
	ADD_RANDOM_UNIT = 4,
	DELETE_RANDOM_UNIT = 5, 
	CLOSE_GAME = 6
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

