#pragma once
#include <Trackable.h>
#include "Steering.h"

class FaceSteering;

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const float theTargetRadians = 0, const float theSlowRadians = 0,	const float theTimeToTarget = 0, 
		const float theWanderOffset = 0, const float theWanderRadius = 0, const float theWanderRate = 0,
		const float theWanderOrientation = 0, const UnitID& targetID = INVALID_UNIT_ID);
	~WanderSteering();
	friend class WanderAndChaseSteering;
protected:
	virtual Steering* getSteering();
private:
	class FaceSteering* mpFaceSteer;
};


