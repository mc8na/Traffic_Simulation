#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

#include "Clock.h"

//Clock::Clock(){}

Clock::Clock(int num, int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west)
{
	// intialize traffic lights per specifications
	ns = TrafficLight(TrafficLight::GREEN, green_north_south, yellow_north_south);
	ew = TrafficLight(TrafficLight::RED, green_east_west, yellow_east_west);
	// create IntSections
	IntSection ne(ew, Lane::WEST); 
	IntSection nw(ns, Lane::SOUTH);
	IntSection se(ns, Lane::NORTH);
	IntSection sw(ew, Lane::EAST);
	// interconnect the IntSections
	ne.setNext(nw);
	nw.setNext(sw);
	sw.setNext(se);
	se.setNext(ne);
	// construct lanes and add to vector
	lanes.push_back(Lane(Lane::NORTH, ne, se, num));
	lanes.push_back(Lane(Lane::WEST, nw, ne, num));
	lanes.push_back(Lane(Lane::SOUTH, sw, nw, num));
	lanes.push_back(Lane(Lane::EAST, se, sw, num));
}

Clock::~Clock() {}

void Clock::Tick() 
{
	ns.advanceTick(); // advance traffic lights by one tick
	ew.advanceTick();
	std::vector<Lane>::iterator it = lanes.begin();
	while(it != lanes.end()) 
	{
		(*it).advance(); // tell each lane to advance its vehicles
		it++;
	}
}

#endif
