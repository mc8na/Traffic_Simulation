#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Vehicle.h"

Vehicle::Vehicle(const Section& sec, Lane::Direction dir)
{
	direction = dir;
}

void proceed()
{

}

Lane::Direction getDirection()
{
	return direction;
}

Vehicle::~Vehicle(){}

#endif
