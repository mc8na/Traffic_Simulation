#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "Lane.h"

Vehicle::Vehicle() {}

Vehicle::Vehicle(Section& sec, Lane::Direction dir)
{
	vDirection = dir;
	front = &sec;
	back = NULL;
}

void Vehicle::proceed()
{
	if((*((*front).getNext())).isOpen() == true)
	{
		if(back != NULL)
		{
			(*back).setOpen(true);
		}
		back = front;
		front = (*front).getNext();
		(*front).setOpen(false);
	}
}

Lane::Direction Vehicle::getDirection()
{
	return vDirection;
}

Vehicle::~Vehicle(){}

#endif
