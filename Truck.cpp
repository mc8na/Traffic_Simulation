#ifndef __TRUCK_CPP__
#define __TRUCK_CPP__

#include "Lane.h"

Truck::Truck() : Vehicle() {}

Truck::Truck(const Truck& truck) : Vehicle(truck)
{
	frontMid = truck.frontMid;
	backMid = truck.backMid;
}

Truck::Truck(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) 
{
	frontMid = NULL;
	backMid = NULL;
}

void Truck::proceed(Lane& lane)
{
	if (front == NULL) 
	{
		(*back).setOpen(true);

		if (frontMid != NULL)
		{
			back = backMid;
			backMid = frontMid;
			frontMid = NULL;
		}
		else if (backMid != NULL) 
		{
			back = backMid;
			backMid = NULL;
		}
		else 
		{
			back = NULL;
			lane.removeVehicle(*this);
		}
	}
	else if ((*front).getNext(vDirection) == NULL)
	{ 
		(*back).setOpen(true);
		back = backMid;
		backMid = frontMid;
		front = NULL;

	}
	if((*((*front).getNext(vDirection))).isOpen() == true) // if next Section is open
	{
		if(back != NULL)
		{
			(*back).setOpen(true); // back sets Section it leaves to open
		}
		// move the Truck forward
		back = backMid;
		backMid = frontMid;
		frontMid = front;
		front = (*front).getNext(vDirection);
		(*front).setOpen(false); // front occupies new Section
	}
}

Truck::~Truck() {}

#endif
