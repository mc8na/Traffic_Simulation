#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

#include "Section.h"

IntSection::IntSection(TrafficLight& tl) : Section() 
{
	traf = tl;
}

void IntSection::setStraight(Section& sec)
{
	next = &sec;
}

void IntSection::setExit(Section& sec)
{
	exit = &sec;
}

IntSection::~IntSection() {}

#endif
