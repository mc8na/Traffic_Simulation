#ifndef __SUV_CPP__
#define __SUV_CPP__

#include "Lane.h"

//SUV::SUV() : Vehicle() {}

SUV::SUV(const SUV& suv) : Vehicle(suv) // const copy constructor
{
	
}

SUV::SUV(Section& sec, Lane::Direction dir) : Vehicle(sec, dir, VehicleBase::SUV) 
{
	location.push_back(&sec);
}

std::vector<Section*> SUV::proceed(Lane& lane)
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
		if(location.back() != nullptr && location.back() != location.at(1))
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

SUV::~SUV() {}

#endif
