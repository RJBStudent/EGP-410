#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"

WanderSteering::WanderSteering(const UnitID& ownerID, const float theTargetRadians, const float theSlowRadians,
	const float theTimeToTarget, const float theWanderOffset, const float theWanderRadius, const float theWanderRate,
	const float theWanderOrientation, const UnitID& targetID)
	: Steering()
{
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setWanderOffset(theWanderOffset);
	setWanderRate(theWanderRate);
	setWanderRadius(theWanderRadius);
	setWanderOrientation(theWanderOrientation);
	setTargetRadians(theTargetRadians);
	setSlowRadians(theSlowRadians);
	setTimeToTarget(theTimeToTarget);
	mpFaceSteer = new FaceSteering(ownerID, mTargetLoc, theTargetRadians, theSlowRadians, theTimeToTarget);
}
WanderSteering::~WanderSteering()
{
	delete mpFaceSteer;
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float targetOrientation;
	Vector2D target;
	
	mWanderOrientation += genRandomBinomial() * mWanderRate;
	targetOrientation = mWanderOrientation + pOwner->getPositionComponent()->getFacing();

 	Vector2D targetOrientationAsVector = Vector2D(cos(targetOrientation), sin(targetOrientation));
	Vector2D characterOrientationAsVector = Vector2D(cos(pOwner->getPositionComponent()->getFacing()), sin(pOwner->getPositionComponent()->getFacing()));

	target = pOwner->getPositionComponent()->getPosition() + characterOrientationAsVector * mWanderOffset;
	target += targetOrientationAsVector * mWanderRadius;
	mpFaceSteer->setTargetLoc(target);

	Steering* faceData = mpFaceSteer->getSteering();
	if (faceData)
	{
		data.rotAcc = faceData->getData().rotAcc;
	}

	characterOrientationAsVector = Vector2D(cos(pOwner->getPositionComponent()->getFacing()), sin(pOwner->getPositionComponent()->getFacing()));
	//Vector2D diff = target - pOwner->getPositionComponent()->getPosition();


	/*
	float velocityDirection = atan2(diff.getY(), diff.getX());
	pOwner->getPositionComponent()->setFacing(velocityDirection);*/
 	data.acc = characterOrientationAsVector * data.maxAccMagnitude;

	this->mData = data;
	return this;
}
