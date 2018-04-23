#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

#include "Clock.h"

//Clock::Clock(){}

Clock::Clock(int num, int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west)
{
	ns = new TrafficLight(TrafficLight::GREEN, green_north_south, yellow_north_south);
	ew = new TrafficLight(TrafficLight::RED, green_east_west, yellow_east_west);
	IntSection ne(*ew, Lane::WEST);
	IntSection nw(*ns, Lane::SOUTH);
	IntSection se(*ns, Lane::NORTH);
	IntSection sw(*ew, Lane::EAST);
	ne.setStraight(nw);
	nw.setStraight(sw);
	sw.setStraight(se);
	se.setStraight(ne);
	Lane *north = new Lane(Lane::NORTH, ne, se, num);
	Lane *west = new Lane(Lane::WEST, nw, ne, num);
	Lane *south = new Lane(Lane::SOUTH, sw, nw, num);
	Lane *east = new Lane(Lane::EAST, se, sw, num);
	lanes.push_back(north);
	lanes.push_back(west);
	lanes.push_back(south);
	lanes.push_back(east);
}

Clock::~Clock(){}

#endif
