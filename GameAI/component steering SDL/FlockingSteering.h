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
	FlockingSteering(const UnitID& ownerID, const float groupRadius = 0);
	~FlockingSteering();
	std::vector<Unit*> createNeighborhood();
protected:
	virtual Steering* getSteering();
private:
	std::vector<BehaviorAndWeight> mBlendedSteeringList;
	float mGroupingRadius;
};