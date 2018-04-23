#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Lane.h"

Section::Section() { open = true; } // Section is not initially occupied

Section::Section(Section& sec)
{
	open = true; // Section is not initially occupied
	next = &sec; // next Section is passed in as parameter
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

void Section::setOpen(bool op) // set whether the Section is occupied or not
{
	open = op;
}

#endif
