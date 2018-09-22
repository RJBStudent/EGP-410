
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
	mpArriveSteer = new ArriveSteering(mOwnerID, mTargetLoc, mTargetRadius, mSlowRadius, mTimeToTarget, mTargetID);
	mpFaceSteer = new FaceSteering(mOwnerID, mTargetLoc, mTargetRadians, mSlowRadians, mTimeToTarget, mTargetID);
}

ArriveAndFaceSteering::~ArriveAndFaceSteering()
{
	delete mpArriveSteer;
	delete mpFaceSteer;
}

Steering* ArriveAndFaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data = mpFaceSteer->getSteering()->getData();	
	pOwner->getPhysicsComponent()->setData(data);
	data = mpArriveSteer->getSteering()->getData();
	//pOwner->getPhysicsComponent()->setData(data);
	this->mData = data;
	return this;
}
