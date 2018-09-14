#pragma once

#include "GameMessage.h"
#include "Vector2D.h"
#include "KeyboardInputs.h"

typedef unsigned char BYTE;

class KeyboardMessage :public GameMessage
{
public:
	KeyboardMessage(BYTE keyState, KeyCode keycode);
	~KeyboardMessage();

	KeyCode getKeyCode() const;
	BYTE getKeyState() const;

	void process();

private:
	KeyCode mKey;
	BYTE mKeyState;
};