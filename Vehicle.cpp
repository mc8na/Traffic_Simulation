#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

//Vehicle::Vehicle() {} // default constructor (not used)

Vehicle::Vehicle(const Vehicle& veh) : VehicleBase(veh)
{
	std::vector<Section*>::const_iterator it = veh.location.cbegin();

	while (it != veh.location.cend()) 
	{
		location.push_back(*it);
		it++;
	}

	vDirection = veh.vDirection;
	(*location.front()).occupy(*this);
}

Vehicle::Vehicle(Section& sec, Lane::Direction dir, VehicleBase::VehicleType type) : VehicleBase(type) // constructor
{
	vDirection = dir; 
	location.push_back(&sec);
	location.push_back(&sec);
	sec.occupy(*this);
}

std::vector<Section*> Vehicle::proceed(Lane& lane)
{
	if (location.front() == nullptr) // if front of vehicle has exited the lane
	{
		(*location.back()).leave(); // back no longer occupies a Section
		location.back() = nullptr;
		lane.removeVehicle(); // remove vehicle from lane
	}
	else if ((*location.front()).getNext(vDirection) == nullptr) // if vehicle about to exit lane
	{ 
		(*location.back()).leave(); // back advances
		location.back() = location.front();
		location.front() = nullptr;

	}
	else if((*((*location.front()).getNext(vDirection))).isOpen(location.front()) == true) // if next Section is open
	{
		if(location.back() != nullptr && location.back() != location.front())
		{
			(*location.back()).leave(); // back sets the Section it leaves to open
		}
		location.back() = location.front(); // move back to next Section
		location.front() = (*location.front()).getNext(vDirection); // move front to next Section
		(*location.front()).occupy(*this); // front occupies the new Section
	} 
	return location;

}

Lane::Direction Vehicle::getDirection() // returns direction vehicle is traveling
{
	return vDirection;
}

void Vehicle::operator=(const Vehicle& veh)
{
	location.clear();
	std::vector<Section*>::const_iterator it = veh.location.cbegin();
	while (it != veh.location.cend()) 
	{
		location.push_back(*it);
		it++;
	}

	vehicleType = veh.getVehicleType();
	vehicleID = veh.getVehicleID();
	vDirection = veh.vDirection;
	(*location.front()).occupy(*this);
}

Vehicle::~Vehicle() {} // deconstructor

#endif
