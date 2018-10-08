#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;

struct BehaviorAndWeight : public Trackable
{
public:
	BehaviorAndWeight(Steering* steer, float weight, float radius) : mSteeringType(steer), mWeight(weight), mRadius(radius){};
	Steering* mSteeringType;
	float mWeight;
	float mRadius;
};

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const float theTargetRadians = 0, const float theSlowRadians = 0, const float theTimeToTarget = 0,
		const float theWanderOffset = 0, const float theWanderRadius = 0, const float theWanderRate = 0,
		const float theWanderOrientation = 0, const float cohesionWeight =0, const float seperationWeight = 0, const float alignmentWeight = 0, const UnitID& targetID = INVALID_UNIT_ID);
	~FlockingSteering();
	std::vector<Unit*> createNeighborhood(float radius);
	

protected:
	virtual Steering* getSteering();
	virtual void IncreaseCohesion();
	virtual void DecreaseCohesion();
	virtual void IncreaseSeperation();
	virtual void DecreaseSeperation();
	virtual void IncreaseAlignment();
	virtual void DecreaseAlignment();

	virtual void SetCohesionWeight(const float cohesion) { mBlendedSteeringList.at(2).mWeight = cohesion; }
	virtual void SetSeperationWeight(const float seperation) { mBlendedSteeringList.at(1).mWeight = seperation; }
	virtual void SetAlignmentWeight(const float alignment) { mBlendedSteeringList.at(3).mWeight = alignment; }

	virtual float GetCohesionWeight() const { return mBlendedSteeringList.at(2).mWeight; }
	virtual float GetSeperationWeight() const { return mBlendedSteeringList.at(1).mWeight; }
	virtual float GetAlignmentWeight() const { return mBlendedSteeringList.at(3).mWeight; }
private:
	std::vector<BehaviorAndWeight> mBlendedSteeringList;
};