#pragma once

#pragma once
#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadians = 0, const float theSlowRadians = 0,
		const float theTimeToTarget = 0, const UnitID& targetID = INVALID_UNIT_ID);
	friend class ArriveAndFaceSteering;
	friend class WanderSteering;
	friend class GroupAlignmentSteering;
	friend class FlockingSteering;
protected:
	virtual Steering* getSteering();
};
