#pragma once
#include <vector>
#include <Trackable.h>
#include "Steering.h"

class Unit;
class SeekSteering;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, std::vector<Unit*> localUnits);
	~CohesionSteering();
	
	friend class FlockingSteering;
protected:
	virtual Steering* getSteering();
	virtual void setNeighborhood(std::vector<Unit*>);
private:
	Vector2D getNeighbourhoodCenter();
	std::vector<Unit*> mLocalUnits;
	SeekSteering* mpSeek;
};