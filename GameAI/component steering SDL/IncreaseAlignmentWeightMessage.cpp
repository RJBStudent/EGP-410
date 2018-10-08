#include "IncreaseAlignmentWeightMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"


IncreaseAlignmentWeightMessage::IncreaseAlignmentWeightMessage()
	:GameMessage(INCREASE_SEPERATION)
{

}
IncreaseAlignmentWeightMessage::~IncreaseAlignmentWeightMessage()
{
}

void IncreaseAlignmentWeightMessage::process()
{
	gpGame->getUnitManager()->IncreaseAllAlignment();
}

