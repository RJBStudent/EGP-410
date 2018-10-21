#include "DepthFirstSearchMessage.h"
#include "GameApp.h"
#include "GridPathfinder.h"

DepthFirstSearchMessage::DepthFirstSearchMessage()
	:GameMessage(DEPTH_FIRST_MESSAGE)
{
}


DepthFirstSearchMessage::~DepthFirstSearchMessage()
{
}

void DepthFirstSearchMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		pGame->setDepthFirst();
		pGame->getPathfinder()->findPath(pGame->getPathfinder()->getLastFrom(), pGame->getPathfinder()->getLastTo());
	}
}
