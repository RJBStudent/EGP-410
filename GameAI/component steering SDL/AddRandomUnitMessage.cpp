#include "Game.h"
#include "GameMessageManager.h"
#include "AddRandomUnitMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "GraphicsSystem.h"

AddRandomUnitMessage::AddRandomUnitMessage()
	:GameMessage(ADD_RANDOM_UNIT)
{
}

AddRandomUnitMessage::~AddRandomUnitMessage()
{
}

void AddRandomUnitMessage::process()
{
	float posX = (rand() % gpGame->getGraphicsSystem()->getWidth());
	float posY = (rand() % gpGame->getGraphicsSystem()->getHeight());

	for(int i = 0; i < 10; i++)
	gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), Vector2D(posX, posY));
}