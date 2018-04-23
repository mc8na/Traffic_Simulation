#ifndef __SUV_CPP__
#define __SUV_CPP__

#include "Lane.h"

SUV::SUV() : Vehicle() {}

SUV::SUV(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) 
{
	mid = NULL;
}

void SUV::proceed()
{
	if((*((*front).getNext())).isOpen() == true)
	{
		if(back != NULL)
		{
			(*back).setOpen(true);
		}
		back = mid;
		mid = front;
		front = (*front).getNext();
		(*front).setOpen(false);
	}
}

SUV::~SUV() {}

#endif
