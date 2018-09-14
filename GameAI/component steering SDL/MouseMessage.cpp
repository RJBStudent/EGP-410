#include "Game.h"
#include "GameMessageManager.h"
#include "MouseMessage.h"

	MouseMessage::MouseMessage(BYTE rightMouseState, BYTE leftMouseState, Vector2D mousePosition) :
		GameMessage(MOUSE_MESSAGE),
		mRightMouseState(rightMouseState),
		mLeftMouseState(leftMouseState),
		mMousePosition(mousePosition)
	{}

	MouseMessage::~MouseMessage()
	{}

	BYTE MouseMessage::getRightMouseState() const 
	{ 
		return mRightMouseState;
	}
	BYTE MouseMessage::getLeftMouseState() const 
	{ 
		return mLeftMouseState;
	}
	Vector2D  MouseMessage::getMouseLocation() const 
	{ 
		return mMousePosition;
	}

	void MouseMessage::process()
	{

	}