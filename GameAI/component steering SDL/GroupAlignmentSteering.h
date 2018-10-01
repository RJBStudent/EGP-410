#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(const UnitID& ownerID, std::vector<Unit*> localUnits);
	~GroupAlignmentSteering();
	friend class FlockingSteering;
protected:
	virtual Steering* getSteering();
	virtual void setNeighborhood(std::vector<Unit*>);
private:
	Vector2D getNeighbourhoodAverageVel();
	std::vector<Unit*> mLocalUnits;
};