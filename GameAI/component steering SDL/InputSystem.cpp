#include "InputSystem.h"
#include "GameMessageManager.h"
#include "defines.h"
#include "Game.h"


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
	mouseInputUpdate();
	for (int i = 0; i < static_cast<int>(KeyCode::NUM_SCANCODES); i++)
	{
		if (mBitwiseKeyStates[i] || 0x0)
		{
			//EventSystem::getInstance()->fireEvent(KeyEvent(mBitwiseKeyStates[i], KeyCode(i)));
			GameMessage* pMessage = new PlayerMoveToMessage(pos);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}

	}
	EventSystem::getInstance()->fireEvent(MouseKeyEvent(mRightMouse, mLeftMouse, mMouseLocation));


}



void InputSystem::mouseInputUpdate()
{
	mLeftMouse &= ~StateBitValues::JUST_PRESSED;

	mLeftMouse &= ~StateBitValues::JUST_RELEASED;

	mRightMouse &= ~StateBitValues::JUST_PRESSED;

	mRightMouse &= ~StateBitValues::JUST_RELEASED;

	SDL_Event ev;

	//Loop through all recorded mouse events

	while (SDL_PollEvent(&ev))
	{


		if (ev.type == SDL_MOUSEMOTION)

		{
			mMouseLocation = Vector2D(ev.motion.x, ev.motion.y);
		}

		else
		{
			BYTE* whichButton = (ev.button.button == SDL_BUTTON_LEFT) ? &mLeftMouse : &mRightMouse;

			if (ev.button.state == SDL_MOUSEBUTTONDOWN)

			{
				*whichButton |= StateBitValues::JUST_PRESSED;
				*whichButton |= StateBitValues::CURRENTLY_PRESSED;
			}
			else if (ev.button.state == SDL_MOUSEBUTTONUP)
			{
				*whichButton &= ~StateBitValues::CURRENTLY_PRESSED;
				*whichButton |= StateBitValues::JUST_RELEASED;
			}
		}
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

