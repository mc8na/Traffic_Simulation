#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

Vehicle::Vehicle() {} // default constructor (not used)

Vehicle::Vehicle(const Vehicle& veh)
{
	front = veh.front;
	back = veh.back;
	vDirection = veh.vDirection;
}

Vehicle::Vehicle(Section& sec, Lane::Direction dir) // constructor
{
	vDirection = dir; 
	front = &sec;
	back = &sec;
}

void Vehicle::proceed(Lane& lane)
{
	if (front == NULL) // if front of vehicle has exited the lane
	{
		(*back).setOpen(true); // back no longer occupies a Section
		back = NULL;
		lane.removeVehicle(); // remove vehicle from lane
	}
	else if ((*front).getNext(vDirection) == NULL) // if vehicle about to exit lane
	{ 
		(*back).setOpen(true); // back advances
		back = front;
		front = NULL;

	}
	if((*((*front).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(back != NULL && back != front)
		{
			(*back).setOpen(true); // back sets the Section it leaves to open
		}
		back = front; // move back to next Section
		front = (*front).getNext(vDirection); // move front to next Section
		(*front).setOpen(false); // front occupies the new Section
	} 

}

Lane::Direction Vehicle::getDirection() // returns direction vehicle is traveling
{
	return vDirection;
}

Vehicle::~Vehicle() {} // deconstructor

#endif
