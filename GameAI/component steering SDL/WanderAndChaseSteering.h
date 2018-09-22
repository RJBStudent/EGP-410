#pragma once
#include <Trackable.h>
#include "Steering.h"

class WanderSteering;
class SeekSteering;

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(const UnitID& ownerID, const float theTargetRadians = 0, const float theSlowRadians = 0,
		const float theTimeToTarget = 0, const float theWanderOffset = 0, const float theWanderRadius = 0, const float theWanderRate = 0,
		const float theWanderOrientation = 0, const float theChaseRadius = 0, const UnitID& targetID = INVALID_UNIT_ID);
	~WanderAndChaseSteering();
protected:
	virtual Steering* getSteering();
private:
	WanderSteering * mpWanderSteer;
	SeekSteering* mpSeekSteer;
};


