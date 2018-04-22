#ifndef __SECTION_CPP__
#define __SECTION_CPP__

//#include "Intersection.h"
#include "Section.h"

Section::Section() {}

Section::Section(const Section& sec)
{
	open = true;
	*next = sec;
}

Section::~Section(){}

bool Section::isOpen()
{
	return open;
}

Section& Section::getNext()
{
	return *next;
}

#endif
