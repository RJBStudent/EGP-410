#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;

struct BehaviorAndWeight : public Trackable
{
public:
	BehaviorAndWeight(Steering* steer, float weight) : mSteeringType(steer), mWeight(weight) {};
	Steering* mSteeringType;
	float mWeight;
};

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const float groupRadius = 0, const float theTargetRadians = 0, const float theSlowRadians = 0, const float theTimeToTarget = 0,
		const float theWanderOffset = 0, const float theWanderRadius = 0, const float theWanderRate = 0,
		const float theWanderOrientation = 0, const UnitID& targetID = INVALID_UNIT_ID);
	~FlockingSteering();
	std::vector<Unit*> createNeighborhood();
protected:
	virtual Steering* getSteering();
private:
	std::vector<BehaviorAndWeight> mBlendedSteeringList;
	float mGroupingRadius;
};