#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

//#include "Intersection.h"
//#include "Vehicle.h"
#include "Lane.h"

Vehicle::Vehicle() {}

Vehicle::Vehicle(const Section& sec, Lane::Direction dir)
{
	vDirection = dir;
}

void Vehicle::proceed()
{

}

Lane::Direction Vehicle::getDirection()
{
	return vDirection;
}

Vehicle::~Vehicle(){}

#endif
