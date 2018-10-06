#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;
class FaceSteering;

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(const UnitID& ownerID, std::vector<Unit*> localUnits);
	~GroupAlignmentSteering();
	friend class FlockingSteering;
protected:
	virtual Steering* getSteering();
	virtual void setNeighbourhood(std::vector<Unit*>  neighbourhood);
private:
	Vector2D getNeighbourhoodAverageVel();
	float getNeighbourhoodAverageDirection();
	std::vector<Unit*> mLocalUnits;
	FaceSteering* mpFace;
};