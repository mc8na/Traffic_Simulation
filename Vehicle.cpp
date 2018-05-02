#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

Vehicle::Vehicle(const Vehicle& veh) : VehicleBase(veh)
{
	location.reserve(4);
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
	location.reserve(4);
	location.push_back(&sec);
	location.push_back(&sec);
	if(type == VehicleBase::SUV)
	{
		location.push_back(&sec);
	}
	else if(type == VehicleBase::TRUCK)
	{
		location.push_back(&sec);
		location.push_back(&sec);
	}
	(*location.front()).occupy(*this);
	vDirection = dir;
}

std::vector<Section*> Vehicle::proceed(Lane& lane)
{
	switch(vehicleType)
	{
		case VehicleBase::CAR:
			return proceedCar(lane);
		case VehicleBase::SUV:
			return proceedSUV(lane);
		case VehicleBase::TRUCK:
			return proceedTruck(lane);
	}
	return location;
}

std::vector<Section*> Vehicle::proceedCar(Lane& lane)
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
		if(location.back() != location.front())
		{
			(*location.back()).leave(); // back sets the Section it leaves to open
		}
		location.back() = location.front(); // move back to next Section
		location.front() = (*location.front()).getNext(vDirection); // move front to next Section
		(*location.front()).occupy(*this); // front occupies the new Section
	} 
	return location;
}

std::vector<Section*> Vehicle::proceedSUV(Lane& lane)
{
	if (location.front() == nullptr) // if front of vehicle has exited the lane
	{
		(*location.back()).leave(); // move back forward

		if (location.at(1) == nullptr) // if vehicle has fully exited the lane
		{
			location.back() = nullptr;
			lane.removeVehicle(); // remove vehicle from lane
		}
		else // if part of vehicle still in the lane
		{
			location.back() = location.at(1); // advance back Section
			location.at(1) = nullptr;
		}
	}
	else if ((*location.front()).getNext(vDirection) == nullptr) // if vehicle about to exit lane
	{ 
		(*location.back()).leave();
		location.back() = location.at(1);
		location.at(1) = location.front();
		location.front() = nullptr;

	}
	else if((*((*location.front()).getNext(vDirection))).isOpen(location.front()) == true) // if next Section is open
	{
		if(location.back() != location.at(1))
		{
			(*location.back()).leave(); // back sets the Section it leaves to open
		}
		location.back() = location.at(1); // move back forward
		location.at(1) = location.front(); // move mid forward
		location.front() = (*location.front()).getNext(vDirection); // move front forward
		(*location.front()).occupy(*this); // front occupies Section
	}
	return location;
}

std::vector<Section*> Vehicle::proceedTruck(Lane& lane)
{
	if (location.front() == nullptr) // if vehicle has walked off end of lane
	{
		(*location.back()).leave(); // move back section forward

		if (location.at(1) != nullptr) // if part of the truck is still in the lane
		{
			location.back() = location.at(2); // advance Sections still in the lane
			location.at(2) = location.at(1);
			location.at(1) = nullptr;
		}
		else if (location.at(2) != nullptr) // if part of the truck is still in the lane
		{
			location.back() = location.at(2); // advance Section still in the lane
			location.at(2) = nullptr;
		}
		else // truck has walked completely off end of the lane, time to remove it
		{
			location.back() = nullptr;
			lane.removeVehicle();
		}
	}
	else if ((*location.front()).getNext(vDirection) == nullptr) // if truck about to walk off end of lane
	{ 
		(*location.back()).leave();
		location.back() = location.at(2);
		location.at(2) = location.at(1);
		location.at(1) = location.front();
		location.front() = nullptr;
	}
	else if((*((*location.front()).getNext(vDirection))).isOpen(location.front()) == true) // if next Section is open
	{
		if(location.back() != location.at(2))
		{
			(*location.back()).leave(); // back sets Section it leaves to open
		}
		// move the Truck forward
		location.back() = location.at(2);
		location.at(2) = location.at(1);
		location.at(1) = location.front();
		location.front() = (*location.front()).getNext(vDirection);
		(*location.front()).occupy(*this); // front occupies new Section
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
	location.reserve(4);
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
