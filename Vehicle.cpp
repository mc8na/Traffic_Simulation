#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

Vehicle::Vehicle() {} // default constructor (not used)

Vehicle::Vehicle(Section& sec, Lane::Direction dir) // constructor
{
	vDirection = dir; 
	front = &sec;
	back = NULL;
}

void Vehicle::proceed()
{
	if((*((*front).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(back != NULL)
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
