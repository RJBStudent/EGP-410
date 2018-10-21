#include "DijkstraPathfindingMessage.h"
#include "GameApp.h"
#include "GridPathfinder.h"

DijkstraPathfindingMessage::DijkstraPathfindingMessage()
	:GameMessage(DIJKSTRA_MESSAGE)
{
}


DijkstraPathfindingMessage::~DijkstraPathfindingMessage()
{
}

void DijkstraPathfindingMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if (pGame != NULL)
	{
		pGame->setDijkstra();
		pGame->getPathfinder()->findPath(pGame->getPathfinder()->getLastFrom(), pGame->getPathfinder()->getLastTo());
	}
}
