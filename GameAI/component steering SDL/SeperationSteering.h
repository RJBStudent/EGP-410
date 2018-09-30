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
	void setNeighborhood(std::vector<Unit*>);
protected:
	virtual Steering* getSteering();
private:

	Vector2D getNeighbourhoodCenter();

	std::vector<Unit*> mLocalUnits;
	SeekSteering* mpFlee;
};