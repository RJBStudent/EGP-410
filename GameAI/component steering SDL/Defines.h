#pragma once

#include <string>
#include <deanlibdefines.h>

typedef int IDType;
typedef std::string IDDescriptor;
typedef std::string GraphicsBufferID;

const IDType INVALID_ID = -1;

const IDType HIGHEST_ID = 9999;

const double PI = 3.1415927;

//Constant variables for Steering
const double TARGET_RADIUS = 0.1;
const double SLOW_RADIUS = 50;
const double TIME_TO_TARGET = 0.1;
const double TARGET_RADIANS = 0.1;
const double SLOW_RADIANS = 0.5;
const double WANDER_OFFSET = 100;
const double WANDER_RADIUS = 30;
const double WANDER_RATE = 6.2831854;
const double WANDER_ORIENTATION = 0;
const double CHASE_RADIUS = 150;

#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()

typedef Uint32 UnitID;

const UnitID INVALID_UNIT_ID = UINT_MAX;
