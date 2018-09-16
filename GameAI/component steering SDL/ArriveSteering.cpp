#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const Steering::SteeringType seekType, const UnitID& targetID)
	: Steering()
{
	mType = seekType;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::SEEK)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else if(mType == Steering::FLEE)
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}
	else if (mType == Steering::ARRIVE)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	/*
	if ((diff - mTargetLoc) == 0)
	{
 		return this;
	}
	*/
 	diff.normalize();
	diff *= pOwner->getMaxAcc();

	//float velocityDirection = atan2(diff.getY(), diff.getX());
	//pOwner->getPositionComponent()->setFacing(velocityDirection);

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;
	//data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
