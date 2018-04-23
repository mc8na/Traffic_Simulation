#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

#include "Clock.h"

Clock::Clock()
{
	ns = TrafficLight(TrafficLight::GREEN, 10, 5);
	ew = TrafficLight(TrafficLight::RED, 10, 5);
}

Clock::Clock(int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west)
{
	ns = TrafficLight(TrafficLight::GREEN, green_north_south, yellow_north_south);
	ew = TrafficLight(TrafficLight::RED, green_east_west, yellow_east_west);
}

Clock::~Clock(){}

#endif
