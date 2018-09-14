#pragma once

#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

typedef unsigned char BYTE;

class MouseMessage : public GameMessage
{
public:
	MouseMessage(BYTE rightMouseState, BYTE leftMouseState, Vector2D mousePosition);
	~MouseMessage();
	BYTE getRightMouseState() const;
	BYTE getLeftMouseState() const;
	Vector2D getMouseLocation() const;

	void process();

private:
	BYTE mRightMouseState;
	BYTE mLeftMouseState;
	Vector2D mMousePosition;
};