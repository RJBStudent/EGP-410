#include "IncreaseSeperationWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


IncreaseSeperationWeightMessage::IncreaseSeperationWeightMessage()
	:GameMessage(INCREASE_SEPERATION)
{

}
IncreaseSeperationWeightMessage::~IncreaseSeperationWeightMessage()
{
}

void IncreaseSeperationWeightMessage::process()
{
	gpGame->getUnitManager()->IncreaseAllSeperation();
}

