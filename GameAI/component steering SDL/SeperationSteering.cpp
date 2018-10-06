#include "SeperationSteering.h"
#include "Unit.h"
#include "Game.h"
#include "UnitManager.h"
#include "SeekSteering.h"

SeperationSteering::SeperationSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mType = Steering::SEPERATION;
	mOwnerID = ownerID;
	mpFlee = new SeekSteering(mOwnerID, ZERO_VECTOR2D, INVALID_UNIT_ID, true);
}

SeperationSteering::~SeperationSteering()
{
	mLocalUnits.clear();
	delete mpFlee;
}

void SeperationSteering::setNeighbourhood(std::vector<Unit*> neighbourhood)
{
	if (mLocalUnits.size() > 0)
	{
		mLocalUnits.clear();
	}
	mLocalUnits = neighbourhood;
}

Steering* SeperationSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D target;
	if (mLocalUnits.size() <= 0)
	{
		return this;
	}

	target = getNeighbourhoodCenter();

	Vector2D newTarget = target - pOwner->getPositionComponent()->getPosition();
	newTarget *= -1;
	newTarget.normalize();
	data.acc = newTarget * data.maxAccMagnitude;

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
	center.setX(center.getX() * (1 / mLocalUnits.size()));
	center.setY(center.getY() *(1 / mLocalUnits.size()));
	return center;
}
