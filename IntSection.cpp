#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

#include "Lane.h"

IntSection::IntSection(const IntSection& sec) : Section(sec) // const copy constructor
{
	open = sec.open;
	next = sec.next;
	out = sec.out;
}

IntSection::IntSection(TrafficLight& tl, Lane::Direction dir, Lane* l, int i) : Section(l, i) // constructor
{
	traf = &tl;
	direction = dir;
}

void IntSection::setExit(Section& sec) // set Section in outbound lane
{
	out = &sec;
}

void IntSection::setLane(Lane& l)
{
	lane = &l;
}

Section* IntSection::getNext(Lane::Direction dir) // returns correct Section based on direction Vehicle travels
{
	if(dir == direction) // next points in direction of IntSection
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
