#pragma once
#include <Vector2D.h>
#include "KeyboardInputs.h"
#include "SDL.h"

typedef unsigned char BYTE;

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

	void update();
	void mouseInputUpdate();
	void keyInputUpdate();
	bool getHasByte(const BYTE value, const BYTE comparison) const;


private:
	/*SDL_KeyboardEvent * mpKeyEvent;
	ALLEGRO_EVENT_QUEUE* mpKeyEventQueue;
	ALLEGRO_EVENT_QUEUE* mpMouseEventQueue;
	*/
	BYTE mBitwiseKeyStates[static_cast<int>(KeyCode::NUM_SCANCODES)];
	BYTE mLeftMouse, mRightMouse;
	Vector2D mMouseLocation;
};

struct StateBitValues
{
	static const BYTE JUST_PRESSED = 0x1;         //0001
	static const BYTE CURRENTLY_PRESSED = 0x2;    //0010
	static const BYTE JUST_RELEASED = 0x4;        //0100
};
