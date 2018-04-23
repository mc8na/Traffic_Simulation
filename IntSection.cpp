#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

#include "Lane.h"

IntSection::IntSection(TrafficLight& tl, Lane::Direction dir) : Section() 
{
	traf = &tl;
	direction = dir;
}

void IntSection::setStraight(Section& sec) // tell IntSection what to point to
{
	next = &sec;
}

void IntSection::setExit(Section& sec) // set Section in outbound lane
{
	exit = &sec;
}

Section* IntSection::getNext(Lane::Direction dir) // returns correct Section based on direction Vehicle travels
{
	if(dir == direction) // next points in direction of IntSection
	{
		return next;
	}
	return exit; // exit points to outbound lane
}

IntSection::~IntSection() {}

#endif
