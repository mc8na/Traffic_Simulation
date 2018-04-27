#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Lane.h"

Section::Section(Lane::Direction l, int i) 
{ 
	open = true; // Section is not initially occupied
	next = NULL;
	lane = l;
	index = i;
}

Section::Section(const Section& sec) // const copy constructor
{
	open = sec.open;
	next = sec.next;
}

Section::~Section(){}

bool Section::isOpen() // returns whether the Section is occupied by a Vehicle
{
	return open;
}

Section* Section::getNext(Lane::Direction dir) // returns the next Section in the Lane
{
	return next;
}

void Section::occupy(Vehicle& veh)
{
	open = false;
	vehicle = &veh;
}

void Section::leave()
{
	open = true;
	vehicle = NULL;
}

void Section::setNext(Section& sec) // sets the Section to point to sec
{
	next = &sec;
}

int Section::getIndex()
{
	return index;
}

Vehicle* Section::getVehicle()
{
	return vehicle;
}

Lane::Direction Section::getLane()
{
	return lane;
}

#endif
