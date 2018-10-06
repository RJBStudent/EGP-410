#include "Game.h"
#include "GameMessageManager.h"
#include "AddRandomUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"

AddRandomUnitMessage::AddRandomUnitMessage()
	:GameMessage(ADD_RANDOM_UNIT)
{
}

AddRandomUnitMessage::~AddRandomUnitMessage()
{
}

void AddRandomUnitMessage::process()
{
	for(int i = 0; i < 10; i++)
	gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID));
}