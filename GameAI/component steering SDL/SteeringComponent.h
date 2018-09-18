#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include "Component.h"
#include "Unit.h"

class PhysicsComponent;
class Steering;
enum Steering::SteeringType;

struct SteeringData : public Trackable
{
	SteeringData():type(Steering::INVALID_TYPE), targetLoc(ZERO_VECTOR2D), ownerID(INVALID_UNIT_ID), targetID(INVALID_UNIT_ID){};
	SteeringData(Steering::SteeringType theType, const Vector2D& theTargetLoc = ZERO_VECTOR2D, UnitID theOwner = INVALID_UNIT_ID, UnitID theTarget = INVALID_UNIT_ID, const float theTargetRadius = 0,
		const float theSlowRadius = 0, const float theTimeToTarget = 0, const float theMaxAcceleration = 0, const float theMaxSpeed = 0)
		:type(theType), targetLoc(theTargetLoc), ownerID(theOwner), targetID(theTarget), targetRadius(theTargetRadius), slowRadius(theSlowRadius),
		timeToTarget(theTimeToTarget), maxAcceleration(theMaxAcceleration), maxSpeed(theMaxSpeed){};
	Steering::SteeringType type;
	Vector2D targetLoc;
	float targetRadius;
	float slowRadius;
	float timeToTarget;
	float maxAcceleration;
	float maxSpeed;
	UnitID ownerID;
	UnitID targetID;
};

const SteeringData ZERO_STEERING_DATA;

class SteeringComponent :public Component
{
public:
	//getters and setters
	Steering::SteeringType getType() const { return mData.type; };
	const Vector2D& getTargetLoc() const { return mData.targetLoc; };
	UnitID getOwnerID() const { return mData.ownerID; };
	UnitID getTargetID() const { return mData.targetID; };
	ComponentID getPhysicsComponentID() const { return mPhysicsComponentID; };
	const SteeringData& getData() const { return mData; };
	void setData(const SteeringData& data);
	void setTargetLoc(const Vector2D& pos) { mData.targetLoc = pos; };
	void setTargetUnitID(const UnitID& id) { mData.targetID = id; };
	void setTargetRadius(const float targetRadius) { mData.targetRadius = targetRadius; }
	void setSlowRadius(const float slowRadius) { mData.slowRadius = slowRadius; }
	void setMaxAcceleration(const float maxAcceleration) { mData.maxAcceleration = maxAcceleration; }
	void setMaxSpeed(const float maxSpeed) { mData.maxSpeed= maxSpeed; }
	void setTImeToTarget(const float timeToTarget) { mData.timeToTarget = timeToTarget; }




	void applySteering(PhysicsComponent& physicsComponent);
private:
	ComponentID mPhysicsComponentID;
	SteeringData mData;
	Steering* mpSteering;
	PhysicsComponent* mpPhysicsComponent=NULL;


	SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID);
	~SteeringComponent();
	void setPhysicsComponent(PhysicsComponent* pComp) { mpPhysicsComponent = pComp; };

	friend class ComponentManager;
};