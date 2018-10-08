#include "InputSystem.h"
#include "GameMessageManager.h"
#include "defines.h"
#include "Game.h"
#include "PlayerMoveToMessage.h"
#include "DeleteRandomUnitMessage.h"
#include "AddRandomUnitMessage.h"
#include "CloseMessage.h"
#include "IncreaseAlignmentWeightMessage.h"
#include "IncreaseCohesionWeightMessage.h"
#include "IncreaseSeperationWeightMessage.h"
#include "DecreaseAlignmentWeightMessage.h"
#include "DecreaseSeperationWeightMessage.h"
#include "DecreaseCohesionWeightMessage.h"

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
	//mouseInputUpdate();
	for (int i = 0; i < static_cast<int>(KeyCode::NUM_SCANCODES); i++)
	{
		if (mBitwiseKeyStates[i] || 0x0)
		{
			if (i == static_cast<int>(KeyCode::SCANCODE_A) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new AddRandomUnitMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_D) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new DeleteRandomUnitMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_U) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new IncreaseSeperationWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_J) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new DecreaseSeperationWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_I) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new IncreaseCohesionWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_K) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new DecreaseCohesionWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_O) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new IncreaseAlignmentWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if (i == static_cast<int>(KeyCode::SCANCODE_L) && getHasByte(mBitwiseKeyStates[i], StateBitValues::JUST_PRESSED))
			{
				GameMessage* pMessage = new DecreaseAlignmentWeightMessage();
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
			else if(i == static_cast<int>(KeyCode::SCANCODE_ESCAPE) && getHasByte(mBitwiseKeyStates[i], StateBitValues::CURRENTLY_PRESSED))
			{
			GameMessage* pMessage = new CloseMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
			}
		}

	}
	if (getHasByte(mLeftMouse, StateBitValues::CURRENTLY_PRESSED))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(mMouseLocation);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

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
	else if(!SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
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

