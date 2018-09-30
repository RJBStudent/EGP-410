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
	void setNeighborhood(std::vector<Unit*>);
protected:
	virtual Steering* getSteering();
private:
	Vector2D getNeighbourhoodCenter();
	std::vector<Unit*> mLocalUnits;
	SeekSteering* mpSeek;
};