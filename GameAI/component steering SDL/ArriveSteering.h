#pragma once
#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const Steering::SteeringType seekType, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
};


