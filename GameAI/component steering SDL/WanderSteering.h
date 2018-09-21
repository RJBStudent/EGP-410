#pragma once
#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius = 0, const float theSlowRadius = 0,
		const float theTimeToTarget = 0, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
};


