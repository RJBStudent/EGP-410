#include "DecreaseCohesionWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


DecreaseCohesionWeightMessage::DecreaseCohesionWeightMessage()
	:GameMessage(INCREASE_COHESION)
{

}
DecreaseCohesionWeightMessage::~DecreaseCohesionWeightMessage()
{
}

void DecreaseCohesionWeightMessage::process()
{
	gpGame->getUnitManager()->DecreaseAllCohesion();
}

