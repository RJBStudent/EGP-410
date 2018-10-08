#include "DecreaseAlignmentWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


DecreaseAlignmentWeightMessage::DecreaseAlignmentWeightMessage()
	:GameMessage(INCREASE_SEPERATION)
{

}
DecreaseAlignmentWeightMessage::~DecreaseAlignmentWeightMessage()
{
}

void DecreaseAlignmentWeightMessage::process()
{
	gpGame->getUnitManager()->DecreaseAllAlignment();
}

