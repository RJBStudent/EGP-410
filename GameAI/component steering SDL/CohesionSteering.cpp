#include "CohesionSteering.h"
#include "UnitManager.h"
#include "SeekSteering.h"
#include "Game.h"

CohesionSteering::CohesionSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mOwnerID = ownerID;
	setNeighborhood(localUnits);
}

CohesionSteering::~CohesionSteering()
{
	mLocalUnits.clear();
	delete mpSeek;
}


void CohesionSteering::setNeighborhood(std::vector<Unit*> neighbourhood)
{
	if (mLocalUnits.size() > 0)
	{
		mLocalUnits.clear();
	}
	mLocalUnits = neighbourhood;
}

Steering* CohesionSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D target;
	if (mLocalUnits.size() <= 0)
	{
		return this;
	}

	target = getNeighbourhoodCenter();

	mpSeek->setTargetLoc = target;
	mpSeek->setOwnerID = mOwnerID;
	data = mpSeek->getSteering()->getData();

	this->mData = data;
	return this;
}

Vector2D CohesionSteering::getNeighbourhoodCenter()
{
	Vector2D center = ZERO_VECTOR2D;
	for (int i = 0; i < mLocalUnits.size(); i++)
	{
		center += mLocalUnits.at(i)->getPositionComponent()->getPosition();
	}
	center *= (1 / mLocalUnits.size());
	return center;
}
