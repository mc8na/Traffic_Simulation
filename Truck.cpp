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
	if((*((*front).getNext())).isOpen() == true)
	{
		if(back != NULL)
		{
			(*back).setOpen(true);
		}
		back = backMid;
		backMid = frontMid;
		frontMid = front;
		front = (*front).getNext();
		(*front).setOpen(false);
	}
}

Truck::~Truck() {}

#endif
