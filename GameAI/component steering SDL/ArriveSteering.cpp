#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius, const float theSlowRadius,
	const float theTimeToTarget, const UnitID& targetID)
	: Steering()
{
	mType = Steering::ARRIVE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setTargetRadius(theTargetRadius);
	setSlowRadius(theSlowRadius);
	setTimeToTarget(theTimeToTarget);
}

Steering* ArriveSteering::getSteering()
{
	float targetSpeed;
	Vector2D diff;
	float distance;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	distance = diff.getLength();

	if (distance < mTargetRadius)
	{
 		return this;
	}

	if (distance > mSlowRadius)
	{
		targetSpeed = data.maxSpeed;
	}
	else
	{
		targetSpeed = data.maxSpeed * distance / mSlowRadius;
	}
	
	Vector2D targetVelocity = diff;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	data.acc = targetVelocity - data.vel;
	data.acc /= mTimeToTarget;

	if (data.acc.getLength() > data.maxAccMagnitude)
	{
		data.acc.normalize();
		data.acc *= data.maxAccMagnitude;
	}
	
	this->mData = data;
	return this;
}
