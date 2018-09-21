
#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "ArriveAndFaceSteering.h"
#include "Unit.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius, const float theSlowRadius,
	const float theTimeToTarget, const UnitID& targetID)
	: Steering()
{
	mType = Steering::ARRIVE_AND_FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setTargetRadius(theTargetRadius);
	setSlowRadius(theSlowRadius);
	setTImeToTarget(theTimeToTarget);
}

Steering* ArriveAndFaceSteering::getSteering()
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


	this->mData = data;
	return this;
}
