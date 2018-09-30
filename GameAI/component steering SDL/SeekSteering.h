#include <Trackable.h>
#include "Steering.h"

class SeekSteering : public Steering
{
public:
	SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	friend class WanderAndChaseSteering;
	friend class SeperationSteering;
	friend class CohesionSteering;
protected:
	virtual Steering* getSteering();
};