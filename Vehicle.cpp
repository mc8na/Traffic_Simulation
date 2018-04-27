#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

//Vehicle::Vehicle() {} // default constructor (not used)

Vehicle::Vehicle(const Vehicle& veh) : VehicleBase(veh.getVehicleType())
{
	std::vector<Section*>::const_iterator it = veh.location.cbegin();

	while (it != veh.location.end()) 
	{
		location.push_back(*it);
		it++;
	}

	vDirection = veh.vDirection;
}

Vehicle::Vehicle(Section& sec, Lane::Direction dir, VehicleBase::VehicleType type) : VehicleBase(type) // constructor
{
	vDirection = dir; 
	location.push_back(&sec);
	location.push_back(&sec);
}

std::vector<Section*> Vehicle::proceed(Lane& lane)
{
	if (location.front() == NULL) // if front of vehicle has exited the lane
	{
		(*location.back()).setOpen(true); // back no longer occupies a Section
		location.back() = NULL;
		lane.removeVehicle(); // remove vehicle from lane
	}
	else if ((*location.front()).getNext(vDirection) == NULL) // if vehicle about to exit lane
	{ 
		(*location.back()).setOpen(true); // back advances
		location.back() = location.front();
		location.front() = NULL;

	}
	if((*((*location.front()).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(location.back() != NULL && location.back() != location.front())
		{
			(*location.back()).setOpen(true); // back sets the Section it leaves to open
		}
		location.back() = location.front(); // move back to next Section
		location.front() = (*location.front()).getNext(vDirection); // move front to next Section
		(*location.front()).setOpen(false); // front occupies the new Section
	} 
	return location;

}

Lane::Direction Vehicle::getDirection() // returns direction vehicle is traveling
{
	return vDirection;
}

Vehicle::~Vehicle() {} // deconstructor

#endif
