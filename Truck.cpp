#ifndef __TRUCK_CPP__
#define __TRUCK_CPP__

#include "Lane.h"

//Truck::Truck() : Vehicle() {}

Truck::Truck(const Truck& truck) : Vehicle(truck)
{
	
}

Truck::Truck(Section& sec, Lane::Direction dir) : Vehicle(sec, dir, VehicleBase::TRUCK) 
{
	
}

std::vector<Section*> Truck::proceed(Lane& lane)
{
	if (location.front() == NULL) // if vehicle has walked off end of lane
	{
		(*location.back()).leave(); // move back section forward

		if (location.at(1) != NULL) // if part of the truck is still in the lane
		{
			location.back() = location.at(2); // advance Sections still in the lane
			location.at(2) = location.at(1);
			location.at(1) = NULL;
		}
		else if (location.at(2) != NULL) // if part of the truck is still in the lane
		{
			location.back() = location.at(2); // advance Section still in the lane
			location.at(2) = NULL;
		}
		else // truck has walked completely off end of the lane, time to remove it
		{
			location.back() = NULL;
			lane.removeVehicle();
		}
	}
	else if ((*location.front()).getNext(vDirection) == NULL) // if truck about to walk off end of lane
	{ 
		(*location.back()).leave();
		location.back() = location.at(2);
		location.at(2) = location.at(1);
		location.front() = NULL;

	}
	if((*((*location.front()).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(location.back() != NULL && location.back() != location.at(2))
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
