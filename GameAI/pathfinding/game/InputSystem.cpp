#include "InputSystem.h"
#include "GameMessageManager.h"
#include "defines.h"
#include "Game.h"
#include "CloseMessage.h"
#include "PathToMessage.h"
#include "GameApp.h"
#include "AStarPathfindingMessage.h"
#include "DijkstraPathfindingMessage.h"
#include "DepthFirstSearchMessage.h"

InputSystem::InputSystem()
{

	init();

}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	mLeftMouse = 0x0;
	mRightMouse = 0x0;
	for (int i = 0; i < static_cast<int>(KeyCode::NUM_SCANCODES); i++)
	{
		mBitwiseKeyStates[i] = 0x0;
	}
}

void InputSystem::cleanup()
{

}

void InputSystem::update()
{
	keyInputUpdate();
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	mouseInputUpdate();

	

	

	//int x, y;
	for (int i = 0; i < static_cast<int>(KeyCode::NUM_SCANCODES); i++)
	{
		if (mBitwiseKeyStates[i] || 0x0)
		{
			if (i == static_cast<int>(KeyCode::SCANCODE_ESCAPE) && getHasByte(mBitwiseKeyStates[i], StateBitValues::CURRENTLY_PRESSED))
			{
				GameMessage* pMessage = new CloseMessage();
				pGame->getMessageManager()->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_F) && getHasByte(mBitwiseKeyStates[i], StateBitValues::CURRENTLY_PRESSED))
			{
				GameMessage* pMessage = new DepthFirstSearchMessage();
				pGame->getMessageManager()->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_D) && getHasByte(mBitwiseKeyStates[i], StateBitValues::CURRENTLY_PRESSED))
			{
				GameMessage* pMessage = new DijkstraPathfindingMessage();
				pGame->getMessageManager()->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_A) && getHasByte(mBitwiseKeyStates[i], StateBitValues::CURRENTLY_PRESSED))
			{
				GameMessage* pMessage = new AStarPathfindingMessage();
				pGame->getMessageManager()->addMessage(pMessage, 0);
			}
		}

	}
	static Vector2D lastPos(0.0f, 0.0f);

	
	if (getHasByte(mLeftMouse, StateBitValues::CURRENTLY_PRESSED))
	{
		Vector2D pos(mMouseLocation.getX(), mMouseLocation.getY());
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			pGame->getMessageManager()->addMessage(pMessage, 0);
			lastPos = pos;
		}
	}

	SDL_PumpEvents();

	//EventSystem::getInstance()->fireEvent(MouseKeyEvent(mRightMouse, mLeftMouse, mMouseLocation));

}



void InputSystem::mouseInputUpdate()
{
	mLeftMouse &= ~StateBitValues::JUST_PRESSED;

	mLeftMouse &= ~StateBitValues::JUST_RELEASED;

	mRightMouse &= ~StateBitValues::JUST_PRESSED;

	mRightMouse &= ~StateBitValues::JUST_RELEASED;

	//Loop through all recorded mouse events

	int x, y;
	SDL_GetMouseState(&x, &y);
	mMouseLocation = Vector2D(x, y);

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		BYTE* whichButton = &mLeftMouse;
		mLeftMouse |= StateBitValues::JUST_PRESSED;
		mLeftMouse |= StateBitValues::CURRENTLY_PRESSED;

	}
	else if (!SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		BYTE* whichButton = &mLeftMouse;
		mLeftMouse &= ~StateBitValues::CURRENTLY_PRESSED;
		mLeftMouse |= StateBitValues::JUST_RELEASED;
	}


	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		BYTE* whichButton = &mRightMouse;
		mRightMouse |= StateBitValues::JUST_PRESSED;
		mRightMouse |= StateBitValues::CURRENTLY_PRESSED;
	}
	else if (!SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		BYTE* whichButton = &mRightMouse;
		mRightMouse &= ~StateBitValues::CURRENTLY_PRESSED;
		mRightMouse |= StateBitValues::JUST_RELEASED;
	}
}

void InputSystem::keyInputUpdate()
{

	SDL_Event ev;
	for (int i = 0; i < static_cast<int>(KeyCode::NUM_SCANCODES); i++)

	{

		//bitwise "and" the bitwise not == "subtract" that bit

		mBitwiseKeyStates[i] &= (~StateBitValues::JUST_PRESSED & ~StateBitValues::JUST_RELEASED);

	}

	while (SDL_PollEvent(&ev))
	{


		if (ev.key.keysym.scancode >= static_cast<int>(KeyCode::NUM_SCANCODES))
			continue;

		if (ev.type == SDL_KEYDOWN)
		{
			mBitwiseKeyStates[ev.key.keysym.scancode] |= StateBitValues::JUST_PRESSED;
			mBitwiseKeyStates[ev.key.keysym.scancode] |= StateBitValues::CURRENTLY_PRESSED;

		}

		else if (ev.type == SDL_KEYUP)
		{
			mBitwiseKeyStates[ev.key.keysym.scancode] &= ~StateBitValues::CURRENTLY_PRESSED;
			mBitwiseKeyStates[ev.key.keysym.scancode] |= StateBitValues::JUST_RELEASED;
		}

	}
}


bool InputSystem::getHasByte(const BYTE value, const BYTE comparison) const
{
	//check if the given comparison bit is set in "value"
	//0101 & 0001 == 0001
	return (value & comparison);

}

