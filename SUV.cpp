#ifndef __SUV_CPP__
#define __SUV_CPP__

#include "Lane.h"

SUV::SUV() : Vehicle() {}

SUV::SUV(const SUV& suv) : Vehicle(suv) // const copy constructor
{
	mid = suv.mid;
}

SUV::SUV(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) 
{
	mid = &sec;
}

void SUV::proceed(Lane& lane)
{
	if (front == NULL) // if front of vehicle has exited the lane
	{
		(*back).setOpen(true); // move back forward

		if (mid != NULL) // if vehicle has fully exited the lane
		{
			back = NULL;
			lane.removeVehicle(); // remove vehicle from lane
		}
		else // if part of vehicle still in the lane
		{
			back = mid; // advance back Section
			mid = NULL;
		}
	}
	else if ((*front).getNext(vDirection) == NULL) // if vehicle about to exit lane
	{ 
		(*back).setOpen(true);
		back = mid;
		mid = front;
		front = NULL;

	}
	if((*((*front).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(back != NULL)
		{
			(*back).setOpen(true); // back sets the Section it leaves to open
		}
		back = mid; // move back forward
		mid = front; // move mid forward
		front = (*front).getNext(vDirection); // move front forward
		(*front).setOpen(false); // front occupies Section
	}
}

SUV::~SUV() {}

#endif
