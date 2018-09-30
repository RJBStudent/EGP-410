#pragma once

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
*/

#include <Vector2D.h>
#include <Trackable.h>
#include "defines.h"
#include "PhysicsComponent.h"



class Steering: public Trackable
{
public:
	enum SteeringType
	{
		INVALID_TYPE = -1,
		SEEK,
		FLEE,
		ARRIVE,
		FACE,
		WANDER,
		WANDER_AND_CHASE,
		ARRIVE_AND_FACE,
		SEPERATION,
		COHESION,
		GROUP_ALIGNEMENT,
		FLOCKING
	};

	//constructors and destructors
	Steering( SteeringType type = INVALID_TYPE ):mType(type), mTargetLoc(ZERO_VECTOR2D), mTargetID(INVALID_UNIT_ID), mOwnerID(INVALID_UNIT_ID), mData(ZERO_PHYSICS_DATA) {};
	virtual ~Steering(){};

	//accessors
	void setTargetLoc(const Vector2D& loc) { mTargetLoc = loc; };
	const Vector2D& getTargetLoc() const { return mTargetLoc; };
	void setTargetID(const UnitID& id) { mTargetID = id; };
	const UnitID& getTargetID() const { return mTargetID; };
	void setOwnerID(const UnitID& id) { mOwnerID = id; };
	void setTargetRadius(const float targetRadius) { mTargetRadius = targetRadius; }
	void setSlowRadius(const float slowRadius) { mSlowRadius = slowRadius; }
	void setTimeToTarget(const float timeToTarget) { mTimeToTarget = timeToTarget; }
	void setSlowRadians(const float slowRadians) { mSlowRadians = slowRadians; }
	void setTargetRadians(const float targetRadians) { mTargetRadians = targetRadians; }
	void setWanderOffset(const float wanderOffset) { mWanderOffset = wanderOffset; }
	void setWanderRadius(const float wanderRadius) { mWanderRadius = wanderRadius; }
	void setWanderRate(const float wanderRate) { mWanderRate = wanderRate; }
	void setWanderOrientation(const float wanderOrientation) { mWanderOrientation = wanderOrientation; }
	void setChaseRadius(const float chaseRadius) { mChaseRadius = chaseRadius; }
	
	//void setData(const PhysicsData& data) { mData = data; };
	const PhysicsData& getData() const { return mData; };
	void update();
	friend class FlockingSteering;
protected:
	SteeringType mType;
	Vector2D mTargetLoc;
	UnitID mTargetID;
	UnitID mOwnerID;
	PhysicsData mData;
	float mTargetRadius;
	float mSlowRadius;
	float mTimeToTarget;
	float mSlowRadians;
	float mTargetRadians;
	float mWanderOffset;
	float mWanderRadius;
	float mWanderRate;
	float mWanderOrientation;
	float mChaseRadius;

	virtual Steering* getSteering() { return this; };//overridden by sub-classes
};
