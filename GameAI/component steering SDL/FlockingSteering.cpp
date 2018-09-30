#include "FlockingSteering.h"
#include "SeperationSteering.h"
#include "CohesionSteering.h"
#include "GroupAlignmentSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"

FlockingSteering::FlockingSteering(const UnitID& ownerID, const float groupRadius)
{
	mOwnerID = ownerID;
	mGroupingRadius = groupRadius;
	std::vector<Unit*> tempList = createNeighborhood();
	mBlendedSteeringList.push_back(BehaviorAndWeight(new SeperationSteering(mOwnerID, tempList) , .5));
	mBlendedSteeringList.push_back(BehaviorAndWeight(new CohesionSteering(mOwnerID, tempList), .5));
	mBlendedSteeringList.push_back(BehaviorAndWeight(new GroupAlignmentSteering(mOwnerID, tempList), .5));

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
	for (std::vector<BehaviorAndWeight>::iterator iter = mBlendedSteeringList.begin(); iter != mBlendedSteeringList.end(); iter++)
	{
		tempData = iter->mSteeringType->getSteering()->getData();
		playerData.vel += tempData.vel * iter->mWeight;
		playerData.rotVel += tempData.rotVel * iter->mWeight;

		totalWeight += iter->mWeight;
	}
	if (totalWeight > 0)
	{
		totalWeight = (1 / totalWeight);
		playerData.vel *= totalWeight;
		playerData.rotVel *= totalWeight;
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
		distance = iter->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
		if (distance.getLength() < mGroupingRadius)
		{
			localUnits.push_back(iter->second);
		}
	}
}