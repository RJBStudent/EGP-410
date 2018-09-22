#pragma once
#include <Trackable.h>
#include "Steering.h"


class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const float theWanderOffset = 0, const float theWanderRadius = 0, const float theWanderRate = 0,
		const float theWanderOrientation = 0, const UnitID& targetID = INVALID_UNIT_ID);
	friend class WanderAndChaseSteering;
protected:
	virtual Steering* getSteering();
private:
};


