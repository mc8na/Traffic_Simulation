#ifndef __SUV_CPP__
#define __SUV_CPP__

#include "Lane.h"

SUV::SUV() : Vehicle() {}

SUV::SUV(const SUV& suv) : Vehicle(suv) 
{
	mid = suv.mid;
}

SUV::SUV(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) 
{
	mid = NULL;
}

void SUV::proceed(Lane& lane)
{
	if (front == NULL) 
	{
		(*back).setOpen(true);

		if (mid == NULL)
		{
			back = NULL;
			lane.removeVehicle(*this);
		}
		else {
			back = mid;
			mid = NULL;
		}
	}
	else if ((*front).getNext(vDirection) == NULL)
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
