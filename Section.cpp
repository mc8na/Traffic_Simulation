#ifndef __SECTION_CPP__
#define __SECTION_CPP__

#include "Lane.h"

Section::Section() { open = true; }

Section::Section(Section& sec)
{
	open = true;
	next = &sec;
}

Section::~Section(){}

bool Section::isOpen()
{
	return open;
}

Section* Section::getNext(Lane::Direction dir)
{
	return next;
}

void Section::setOpen(bool op)
{
	open = op;
}

#endif
