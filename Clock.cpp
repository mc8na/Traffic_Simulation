#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

#include "Clock.h"

//Clock::Clock(){}

Clock::Clock(int num, int green_north_south, int yellow_north_south, 
	         int green_east_west, int yellow_east_west, double prob_new_vehicle_north_south,
			 double prob_new_vehicle_east_west, double proportion_of_cars,
			 double proportion_of_SUVs, double prob_right_turn_cars,
			 double prob_right_turn_SUVs, double prob_right_turn_trucks)
{
	// intialize traffic lights per specifications
	ns = TrafficLight(TrafficLight::GREEN, green_north_south, yellow_north_south);
	ew = TrafficLight(TrafficLight::RED, green_east_west, yellow_east_west);
	// create IntSections
	IntSection ne(ew, Lane::WEST, NULL, num); 
	IntSection nw(ns, Lane::SOUTH, NULL, num);
	IntSection se(ns, Lane::NORTH, NULL, num);
	IntSection sw(ew, Lane::EAST, NULL, num);
	// interconnect the IntSections
	ne.setNext(nw);
	nw.setNext(sw);
	sw.setNext(se);
	se.setNext(ne);
	// construct lanes and add to vector
	lanes.push_back(Lane(Lane::NORTH, ne, se, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks));
	lanes.push_back(Lane(Lane::WEST, nw, ne, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks));
	lanes.push_back(Lane(Lane::SOUTH, sw, nw, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks));
	lanes.push_back(Lane(Lane::EAST, se, sw, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks));
}

Clock::~Clock() {}

std::vector<Section*> Clock::Tick() 
{
	ns.advanceTick(); // advance traffic lights by one tick
	ew.advanceTick();
	std::vector<Section*> occupied;
	std::vector<Section*> temp;
	std::vector<Lane>::iterator it = lanes.begin();
	while(it != lanes.end()) 
	{
		temp = (*it).advance(); // tell each lane to advance its vehicles
		std::vector<Section*>::iterator it2 = temp.begin();
		while(it2 != temp.end())
		{
			occupied.push_back(*it2);
			it2++;
		}
		it++;
	}
	return occupied;
}

#endif
