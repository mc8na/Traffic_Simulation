#ifndef __TRUCK_CPP__
#define __TRUCK_CPP__

#include "Lane.h"

//Truck::Truck() : Vehicle() {}

Truck::Truck(const Truck& truck) : Vehicle(truck)
{
	
}

Truck::Truck(Section& sec, Lane::Direction dir) : Vehicle(sec, dir, VehicleBase::TRUCK) 
{
	location.push_back(&sec);
	location.push_back(&sec);
}

std::vector<Section*> Truck::proceed(Lane& lane)
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
		location.front() = nullptr;

	}
	if((*((*location.front()).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(location.back() != nullptr && location.back() != location.at(2))
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

Truck::~Truck() {}

#endif
