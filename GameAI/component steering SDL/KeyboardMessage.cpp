#include "Game.h"
#include "GameMessageManager.h"
#include "KeyboardMessage.h"

KeyboardMessage::KeyboardMessage(BYTE keyState, KeyCode keycode) :
	GameMessage(KEYBOARD_MESSAGE),
	mKeyState(keyState),
	mKey(keycode) 
{
}

KeyboardMessage::~KeyboardMessage()
{

}

KeyCode KeyboardMessage::getKeyCode() const
{ 
	return mKey; 
}

BYTE KeyboardMessage::getKeyState() const 
{ 
	return mKeyState;
}

void KeyboardMessage::process()
{

}