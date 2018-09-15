#include "Game.h"
#include "GameMessageManager.h"
#include "CloseMessage.h"
#include "UnitManager.h"

CloseMessage::CloseMessage()
	:GameMessage(CLOSE_GAME)
{
}

CloseMessage::~CloseMessage()
{
}

void CloseMessage::process()
{
	gpGame->setShouldExit(true);
}