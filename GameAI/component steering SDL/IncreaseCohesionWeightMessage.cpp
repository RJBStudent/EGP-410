#include "IncreaseCohesionWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


IncreaseCohesionWeightMessage::IncreaseCohesionWeightMessage()
	:GameMessage(INCREASE_COHESION)
{

}
IncreaseCohesionWeightMessage::~IncreaseCohesionWeightMessage()
{
}

void IncreaseCohesionWeightMessage::process()
{
	gpGame->getUnitManager()->IncreaseAllCohesion();
}

