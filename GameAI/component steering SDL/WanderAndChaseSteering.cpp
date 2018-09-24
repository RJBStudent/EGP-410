#include <cassert>

#include "Steering.h"
#include "WanderAndChaseSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "SeekSteering.h"

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID& ownerID, const float theTargetRadians, const float theSlowRadians,
	const float theTimeToTarget, const float theWanderOffset, const float theWanderRadius, const float theWanderRate,
	const float theWanderOrientation, const float theChaseRadius, const UnitID& targetID)
	: Steering()
{
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetRadians(theTargetRadians);
	setSlowRadians(theSlowRadians);
	setWanderOffset(theWanderOffset);
	setWanderRate(theWanderRate);
	setWanderRadius(theWanderRadius);
	setWanderOrientation(theWanderOrientation);
	setTimeToTarget(theTimeToTarget);
	setChaseRadius(theChaseRadius);
	mpSeekSteer = new SeekSteering(mOwnerID, ZERO_VECTOR2D, targetID);
	mpWanderSteer = new WanderSteering(mOwnerID, mTargetRadians, mSlowRadians, mTimeToTarget,mWanderOffset, mWanderRadius, mWanderRate, mWanderOrientation);
}
WanderAndChaseSteering::~WanderAndChaseSteering()
{
	delete mpSeekSteer;
	delete mpWanderSteer;
}

Steering* WanderAndChaseSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	Vector2D diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	float distance = diff.getLength();
	if (distance > mChaseRadius)
	{
		data = mpWanderSteer->getSteering()->getData();
		pOwner->getPhysicsComponent()->setData(data);
		
	}
	else
	{
		data = mpSeekSteer->getSteering()->getData();
		pOwner->getPhysicsComponent()->setData(data);
	}
	this->mData = data; 
	return this;
}