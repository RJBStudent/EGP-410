#include "GroupAlignmentSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Steering.h"
#include "FaceSteering.h"

GroupAlignmentSteering::GroupAlignmentSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mOwnerID = ownerID;
	setNeighbourhood(localUnits);
	mpFace = new FaceSteering(ownerID, ZERO_VECTOR2D, TARGET_RADIANS, SLOW_RADIANS, TIME_TO_TARGET);
}

GroupAlignmentSteering::~GroupAlignmentSteering()
{
	mLocalUnits.clear();
	delete mpFace;
}

void GroupAlignmentSteering::setNeighbourhood(std::vector<Unit*> neighbourhood)
{
	if (mLocalUnits.size() > 0)
	{
		mLocalUnits.clear();
	}
	mLocalUnits = neighbourhood;
}

Steering* GroupAlignmentSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	if (mLocalUnits.size() <= 0)
	{
		return this;
	}

	float averageRot = getNeighbourhoodAverageDirection();
	Vector2D targetVel = Vector2D(cos(averageRot), sin(averageRot));

	//Vector2D targetVel = getNeighbourhoodAverageVel();
	//targetVel.normalize();
	mpFace->setTargetLoc(targetVel);
	data.rotAcc = mpFace->getSteering()->getData().rotAcc;

	this->mData = data;
	return this;
}

float GroupAlignmentSteering::getNeighbourhoodAverageDirection()
{
	float centerVel = 0;
	int i;
	for (i = 0; i < mLocalUnits.size(); i++)
	{
		centerVel += mLocalUnits.at(i)->getPositionComponent()->getFacing();
	}
	centerVel += gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getFacing();

	centerVel /= i + 1;
	return centerVel;
}


Vector2D GroupAlignmentSteering::getNeighbourhoodAverageVel()
{
	Vector2D centerVel = ZERO_VECTOR2D;
	int i;
	for (i = 0; i < mLocalUnits.size(); i++)
	{
		centerVel += mLocalUnits.at(i)->getPhysicsComponent()->getVelocity();
	}
	if (i == 0)
	{
		return ZERO_VECTOR2D;
	}
	centerVel += gpGame->getUnitManager()->getUnit(mOwnerID)->getPositionComponent()->getPosition();
	centerVel.setX(centerVel.getX() / i + 1);
	centerVel.setY(centerVel.getY() / i + 1);
	return centerVel;
}