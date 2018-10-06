#include "FlockingSteering.h"
#include "SeperationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignmentSteering.h"
#include "WanderSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"

FlockingSteering::FlockingSteering(const UnitID& ownerID, const float groupRadius, const float theTargetRadians, const float theSlowRadians,
	const float theTimeToTarget, const float theWanderOffset, const float theWanderRadius, const float theWanderRate,
	const float theWanderOrientation, const UnitID& targetID)
{
	mType = Steering::FLOCKING;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetRadians(theTargetRadians);
	setSlowRadians(theSlowRadians);
	setWanderOffset(theWanderOffset);
	setWanderRate(theWanderRate);
	setWanderRadius(theWanderRadius);
	setWanderOrientation(theWanderOrientation);
	setTimeToTarget(theTimeToTarget);
	mGroupingRadius = groupRadius;
	std::vector<Unit*> tempList = createNeighborhood();
	mBlendedSteeringList.push_back(BehaviorAndWeight(new WanderSteering(mOwnerID, mTargetRadians, mSlowRadians, mTimeToTarget, mWanderOffset, mWanderRadius, mWanderRate, mWanderOrientation), .5));
	mBlendedSteeringList.push_back(BehaviorAndWeight(new SeperationSteering(mOwnerID, tempList) , .1));
	mBlendedSteeringList.push_back(BehaviorAndWeight(new CohesionSteering(mOwnerID, tempList), .5));
	mBlendedSteeringList.push_back(BehaviorAndWeight(new GroupAlignmentSteering(mOwnerID, tempList), .4));

}

FlockingSteering::~FlockingSteering()
{
	for (int i = 0; i < mBlendedSteeringList.size(); i++)
	{
		delete mBlendedSteeringList.at(i).mSteeringType;
	}
	mBlendedSteeringList.clear();
}

Steering* FlockingSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData playerData = pOwner->getPhysicsComponent()->getData();
	PhysicsData tempData;
	float totalWeight = 0;
	std::vector<Unit*> tempList = createNeighborhood();
	//wander First
	tempData = mBlendedSteeringList.begin()->mSteeringType->getSteering()->getData();
	playerData.acc += tempData.acc;
	playerData.rotAcc += tempData.rotAcc;
	this->mData = playerData;
	//Rest of the steering methods
	for (std::vector<BehaviorAndWeight>::iterator iter = mBlendedSteeringList.begin()+1; iter != mBlendedSteeringList.end(); iter++)
	{
		iter->mSteeringType->setNeighbourhood(tempList);
		tempData = iter->mSteeringType->getSteering()->getData();
		playerData.acc += tempData.acc * iter->mWeight;
		playerData.rotAcc += tempData.rotAcc * iter->mWeight;

		totalWeight += iter->mWeight;
		this->mData = playerData;
	}
	if (totalWeight > 0)
	{
		totalWeight = (1 / totalWeight);
		playerData.acc *= totalWeight;
		playerData.rotAcc *= totalWeight;
	}
	this->mData = playerData;
	return this;
}

std::vector<Unit*> FlockingSteering::createNeighborhood()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	std::vector<Unit*> localUnits;
	std::map<UnitID, Unit*> unitMap = gpGame->getUnitManager()->getUnitMap();
	Vector2D distance;
	for (std::map<UnitID, Unit*>::iterator iter = unitMap.begin(); iter != unitMap.end(); iter++)
	{
		if (iter->second->getPositionComponent()->getID() == mOwnerID)
		{
			continue;
		}
		distance = iter->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
		if (distance.getLength() < mGroupingRadius)
		{
			localUnits.push_back(iter->second);
		}
	}
	return localUnits;
}