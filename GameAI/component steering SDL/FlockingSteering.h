#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

struct BehaviorAndWeight : public Trackable
{
public:
	BehaviorAndWeight(Steering steer, float weight) : mSteeringType(steer), mWeight(weight) {};
	Steering mSteeringType;
	float mWeight;
};

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID);
protected:
	virtual Steering* getSteering();
private:
	std::vector<BehaviorAndWeight> mBlendedSteeringList;
};