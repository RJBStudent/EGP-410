#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "ArriveAndFaceSteering.h"
#include "WanderSteering.h"
#include "WanderAndChaseSteering.h"

SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID) 
	:Component(id)
	, mPhysicsComponentID(physicsComponentID)
	, mpSteering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data)
{
	mData = data;

	switch (data.type)
	{
	case Steering::SEEK:
	{
		//cleanup old steering - todo: check for already existing steering and reuse if possible
		delete mpSteering;
		//create new steering
		mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, false);
		break;
	}
	case Steering::FLEE:
	{
		delete mpSteering;
		mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, true);
		break;
	}
	case Steering::ARRIVE:
	{
		delete mpSteering;
		mpSteering = new ArriveSteering(data.ownerID, data.targetLoc, data.targetRadius, data.slowRadius, data.timeToTarget, data.targetID);
		break;
	}
	case Steering::FACE:
	{
		delete mpSteering;
		mpSteering = new FaceSteering(data.ownerID, data.targetLoc, data.targetRadians, data.slowRadians, data.timeToTarget, data.targetID);
		break;
	}
	case Steering::ARRIVE_AND_FACE:
	{
		delete mpSteering;
		mpSteering = new ArriveAndFaceSteering(data.ownerID, data.targetLoc, data.targetRadius, data.slowRadius, data.timeToTarget, data.targetRadians, data.slowRadians, data.targetID);
		break;
	}
	case Steering::WANDER:
	{
		delete mpSteering;
		mpSteering = new WanderSteering(data.ownerID, data.wanderOffset, data.wanderRadius, data.wanderRate, data.wanderOrientation);
		break;
	}
	case Steering::WANDER_AND_CHASE:
	{
		delete mpSteering;
		mpSteering = new WanderAndChaseSteering(data.ownerID, data.targetRadians, data.slowRadians, data.timeToTarget, data.wanderOffset, data.wanderRadius, data.wanderRate, data.wanderOrientation, data.chaseRadius, data.targetID);
		break;
	}
		default:
		{

		}
	};
}

