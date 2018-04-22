#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

//#include "Intersection.h"
#include "Clock.h"

Clock::Clock()
{
	ns = TrafficLight(TrafficLight::GREEN, 10, 5);
	ew = TrafficLight(TrafficLight::RED, 10, 5);
}

Clock::~Clock(){}

#endif
