#include "SeperationSteering.h"
#include "Unit.h"
#include "Game.h"
#include "UnitManager.h"
#include "SeekSteering.h"

SeperationSteering::SeperationSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mType = Steering::SEPERATION;
	mOwnerID = ownerID;
}

SeperationSteering::~SeperationSteering()
{

}

Steering* SeperationSteering::getSteering()
{	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D target;
	if (mLocalUnits.size() <= 0)
	{
		return this;
	}
	
	target = getNeighbourhoodCenter();

	mpFlee->setTargetLoc = target;
	mpFlee->setOwnerID = mOwnerID;
	data = mpFlee->getSteering()->getData();
	
	this->mData = data;
	return this;
}

Vector2D SeperationSteering::getNeighbourhoodCenter()
{
	Vector2D center = ZERO_VECTOR2D;
	for (int i = 0; i < mLocalUnits.size(); i++)
	{
		center += mLocalUnits.at(i)->getPositionComponent()->getPosition();
	}
	center *= (1 / mLocalUnits.size());
	return center;
}
