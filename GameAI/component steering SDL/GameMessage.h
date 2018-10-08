#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PLAYER_ARRIVE_AND_SEEK = 1,
	ADD_RANDOM_UNIT = 2,
	DELETE_RANDOM_UNIT = 3, 
	CLOSE_GAME = 4,
	INCREASE_SEPERATION = 5,
	INCREASE_COHESION = 6,
	INCREASE_ALIGNMENT = 7,
	DECREASE_SEPERATION = 8,
	DECREASE_COHESION = 9,
	DECREASE_ALIGNMENT = 10,

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

