#include "AStarPathfindingMessage.h"
#include "GameApp.h"
#include "GridPathfinder.h"

AStarPathfindingMessage::AStarPathfindingMessage()
	:GameMessage(A_STAR_MESSAGE)

{
}


AStarPathfindingMessage::~AStarPathfindingMessage()
{
}

void AStarPathfindingMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		pGame->setAStar();
		pGame->getPathfinder()->findPath(pGame->getPathfinder()->getLastFrom(), pGame->getPathfinder()->getLastTo());
	}
}
