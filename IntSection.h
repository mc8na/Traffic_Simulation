#ifndef __INTSECTION_H__
#define __INTSECTION_H__

#include "Section.h"
#include "TrafficLight.h"

class IntSection : public Section
{
	public:
		IntSection(Section straight, Section turn, TrafficLight tl);
		~IntSection();

	protected:
		TrafficLight traf;
		Section exit;

};

#endif
