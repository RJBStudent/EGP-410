#include "CohesionSteering.h"
#include "UnitManager.h"
#include "SeekSteering.h"
#include "Game.h"

CohesionSteering::CohesionSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mOwnerID = ownerID;
	setNeighbourhood(localUnits);
	mpSeek = new SeekSteering(mOwnerID, ZERO_VECTOR2D);
}

CohesionSteering::~CohesionSteering()
{
	mLocalUnits.clear();
	delete mpSeek;
}


void CohesionSteering::setNeighbourhood(std::vector<Unit*> neighbourhood)
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
	/*
	mpSeek->setTargetLoc(target);
	mpSeek->setOwnerID(mOwnerID);
	data = mpSeek->getSteering()->getData();
	*/
	Vector2D newTarget = target - pOwner->getPositionComponent()->getPosition();
	newTarget.normalize();
	//newTarget += pOwner->getPositionComponent()->getPosition();
	data.acc = newTarget * data.maxAccMagnitude;

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

	center.setX(center.getX() /mLocalUnits.size());
	center.setY(center.getY() / mLocalUnits.size());

	return center;
}
