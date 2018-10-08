#include "DecreaseSeperationWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


DecreaseSeperationWeightMessage::DecreaseSeperationWeightMessage()
	:GameMessage(DECREASE_SEPERATION)
{

}
DecreaseSeperationWeightMessage::~DecreaseSeperationWeightMessage()
{
}

void DecreaseSeperationWeightMessage::process()
{
	gpGame->getUnitManager()->DecreaseAllSeperation();
}

