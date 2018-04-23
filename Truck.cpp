#ifndef __TRUCK_CPP__
#define __TRUCK_CPP__

#include "Lane.h"

Truck::Truck() : Vehicle() {}

Truck::Truck(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) 
{
	frontMid = NULL;
	backMid = NULL;
}

void Truck::proceed()
{
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
