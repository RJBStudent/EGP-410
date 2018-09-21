#pragma once
#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius = 0, const float theSlowRadius = 0,
		const float theTimeToTarget = 0, const UnitID& targetID = INVALID_UNIT_ID);
	friend class ArriveAndFaceSteering;
protected:
	virtual Steering* getSteering();
};


