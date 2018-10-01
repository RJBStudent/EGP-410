#include "GroupAlignmentSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Steering.h"

GroupAlignmentSteering::GroupAlignmentSteering(const UnitID& ownerID, std::vector<Unit*> localUnits)
{
	mOwnerID = ownerID;
	setNeighborhood(localUnits);
}

GroupAlignmentSteering::~GroupAlignmentSteering()
{
	mLocalUnits.clear();
}

void GroupAlignmentSteering::setNeighborhood(std::vector<Unit*> neighbourhood)
{
	if (mLocalUnits.size() > 0)
	{
		mLocalUnits.clear();
	}
	mLocalUnits = neighbourhood;
}

Steering* GroupAlignmentSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	if(mLocalUnits.size() <= 0)
	{
		return this;
	}
	Vector2D targetVel = getNeighbourhoodAverageVel();
	
	data.acc = targetVel - data.acc;
	if (data.acc.getLength() > data.maxAccMagnitude*data.maxAccMagnitude)
	{
		data.acc.normalize();
		data.acc *= data.maxAccMagnitude;
	}
	this->mData = data;
	return this;
}


Vector2D GroupAlignmentSteering::getNeighbourhoodAverageVel()
{
	Vector2D centerVel = ZERO_VECTOR2D;
	for (int i = 0; i < mLocalUnits.size(); i++)
	{
		centerVel += mLocalUnits.at(i)->getPhysicsComponent()->getVelocity();
	}
	centerVel *= (1 / mLocalUnits.size());
	return centerVel;
}