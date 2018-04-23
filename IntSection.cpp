#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

#include "Lane.h"

IntSection::IntSection(TrafficLight& tl, Lane::Direction dir) : Section() 
{
	traf = &tl;
	direction = dir;
}

void IntSection::setStraight(Section& sec)
{
	next = &sec;
}

void IntSection::setExit(Section& sec)
{
	exit = &sec;
}

Section* IntSection::getNext(Lane::Direction dir)
{
	if(dir == direction)
	{
		return next;
	}
	return exit;
}

IntSection::~IntSection() {}

#endif
