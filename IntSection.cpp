#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

#include "Lane.h"

IntSection::IntSection(const IntSection& sec) : Section(sec) // const copy constructor
{
	traf = sec.traf;
	out = sec.out;
}

IntSection::IntSection(TrafficLight& tl, Lane::Direction dir, int i) : Section(dir, i) // constructor
{
	traf = &tl;
}

void IntSection::setExit(Section& sec) // out points to Section in outbound lane
{
	out = &sec;
}

Section* IntSection::getNext(Lane::Direction dir) // returns correct Section based on direction Vehicle travels
{
	if(dir == lane) // next points in direction of IntSection
	{
		return next;
	}
	return out; // out points to outbound lane
}

bool IntSection::isOpen()
{
	if((*traf).getColor() == TrafficLight::GREEN) // if the vehicle has a green light
	{
		return open; // return whether the IntSection is occupied
	}
	return false; // if the light is yellow or red, do not advance vehicle
}

IntSection::~IntSection() {}

#endif
