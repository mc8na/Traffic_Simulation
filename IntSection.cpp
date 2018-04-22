#ifndef __INTSECTION_CPP__
#define __INTSECTION_CPP__

//#include "Intersection.h"
#include "IntSection.h"

IntSection::IntSection(Section straight, Section turn, TrafficLight tl) : Section(straight) 
{
	exit = turn;
	traf = tl;
}

IntSection::~IntSection() {}

#endif
