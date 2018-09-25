#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadians, const float theSlowRadians,
	const float theTimeToTarget, const UnitID& targetID)
	: Steering()
{
	mType = Steering::FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setTargetRadians(theTargetRadians);
	setSlowRadians(theSlowRadians);
	setTimeToTarget(theTimeToTarget);
}

Steering* FaceSteering::getSteering()
{
	float targetSpeed;
	Vector2D diff;
	float distance;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float targetOrientation;
	float rotDiff;

	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}
	
	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	targetOrientation = atan2(diff.getY(), diff.getX());

 	if (diff.getLength() == 0)
	{
		return this;
	}

	rotDiff = targetOrientation - pOwner->getPositionComponent()->getFacing();



	rotDiff = fmod(rotDiff, 2*PI);

	if (rotDiff > PI)
	{
		rotDiff = (2*PI - rotDiff );
	}
	else if (rotDiff <-PI)
	{
		rotDiff = (2*PI + rotDiff);
	}
	float targetRotation;

	float rotationSize = abs(rotDiff);

	if (rotationSize <= mTargetRadians)
	{
		data.rotAcc = 0;
		this->mData = data;
		return this;
	}
	if (rotationSize > mSlowRadians)
	{
 		targetRotation = data.maxRotVel;
	}
	else
	{
		targetRotation = data.maxRotVel * rotationSize / mSlowRadians;
	}
	targetRotation *= targetOrientation / rotationSize;

	data.rotAcc = rotDiff - data.rotVel;
	data.rotAcc /= mTimeToTarget;

	float angularAcceleration = abs(data.rotAcc);
	if (angularAcceleration > pOwner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= pOwner->getMaxRotAcc();
	}

	this->mData = data;
	return this;
}
