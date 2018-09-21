
#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "ArriveAndFaceSteering.h"
#include "Unit.h"
#include "FaceSteering.h"
#include "ArriveSteering.h"


ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const float theTargetRadius, const float theSlowRadius,
	const float theTimeToTarget, const float theTargetRadians, const float theSlowRadians, const UnitID& targetID)
	: Steering()
{
	mType = Steering::ARRIVE_AND_FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	setTargetRadius(theTargetRadius);
	setSlowRadius(theSlowRadius);
	setTimeToTarget(theTimeToTarget);
	mArriveSteer = new ArriveSteering(mOwnerID, mTargetLoc, mTargetRadius, mSlowRadius, mTimeToTarget, mTargetID);
	mFaceSteer = new FaceSteering(mOwnerID, mTargetLoc, mTargetRadians, mSlowRadians, mTimeToTarget, mTargetID);
}

ArriveAndFaceSteering::~ArriveAndFaceSteering()
{
	delete mArriveSteer;
	delete mFaceSteer;
}

Steering* ArriveAndFaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data = mFaceSteer->getSteering()->getData();	
	pOwner->getPhysicsComponent()->setData(data);
	data = mArriveSteer->getSteering()->getData();
	//pOwner->getPhysicsComponent()->setData(data);
	this->mData = data;
	return this;
}
