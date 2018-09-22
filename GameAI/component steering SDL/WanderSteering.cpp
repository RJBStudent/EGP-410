#include <cassert>

#include "Steering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderSteering::WanderSteering(const UnitID& ownerID, const float theWanderOffset, const float theWanderRadius, const float theWanderRate, 
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

	target = pOwner->getPositionComponent()->getPosition() + characterOrientationAsVector.operator*(mWanderOffset);

	target += targetOrientationAsVector.operator*(mWanderRadius);
	characterOrientationAsVector = Vector2D(cos(pOwner->getPositionComponent()->getFacing()), sin(pOwner->getPositionComponent()->getFacing()));
	Vector2D diff = target - pOwner->getPositionComponent()->getPosition();

	float velocityDirection = atan2(diff.getY(), diff.getX());
	pOwner->getPositionComponent()->setFacing(velocityDirection);
 	data.acc = characterOrientationAsVector.operator*(data.maxAccMagnitude);

	this->mData = data;
	return this;
}
