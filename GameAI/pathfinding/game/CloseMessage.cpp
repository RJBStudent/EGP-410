#include "CloseMessage.h"
#include "Game.h"
#include "GameApp.h"

CloseMessage::CloseMessage()
	:GameMessage(CLOSE_MESSAGE)
{
}

CloseMessage::~CloseMessage()
{
}

void CloseMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		pGame->markForExit();
	}
}