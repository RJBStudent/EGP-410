#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;
class SeekSteering;

class SeperationSteering:public Steering
{
public:
	SeperationSteering(const UnitID& ownerID, std::vector<Unit*> localUnits);
	~SeperationSteering();
	
	friend class FlockingSteering;
protected:
	virtual Steering* getSteering();
	virtual void setNeighborhood(std::vector<Unit*>);
private:

	Vector2D getNeighbourhoodCenter();

	std::vector<Unit*> mLocalUnits;
	SeekSteering* mpFlee;
};