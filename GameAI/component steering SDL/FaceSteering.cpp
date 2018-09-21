#include <cassert>

#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius, const float theSlowRadius,
	const float theTimeToTarget, const UnitID& targetID)
	: Steering()
{
	mType = Steering::FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setTargetRadius(theTargetRadius);
	setSlowRadius(theSlowRadius);
	setTImeToTarget(theTimeToTarget);
}

Steering* FaceSteering::getSteering()
{
	float targetSpeed;
	Vector2D diff;
	float distance;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float orientation;

	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	if (diff.getLength() == 0)
	{
		return this;
	}

	float velocityDirection = atan2(diff.getY(), diff.getX());
	pOwner->getPositionComponent()->setFacing(velocityDirection);


	

	this->mData = data;
	return this;
}
