#ifndef __CLOCK_CPP__
#define __CLOCK_CPP__

#include "Clock.h"

//Clock::Clock(){}

Clock::Clock(int num, int green_north_south, int yellow_north_south, 
	         int green_east_west, int yellow_east_west, double prob_new_vehicle_north_south,
			 double prob_new_vehicle_east_west, double proportion_of_cars,
			 double proportion_of_SUVs, double prob_right_turn_cars,
			 double prob_right_turn_SUVs, double prob_right_turn_trucks) : 
			 ns(TrafficLight(TrafficLight::GREEN, green_north_south, yellow_north_south)),
			 ew(TrafficLight(TrafficLight::RED, green_east_west, yellow_east_west)),
			 ne(IntSection(ew, Lane::WEST, num)), nw(IntSection(ns, Lane::SOUTH, num)),
			 se(IntSection(ns, Lane::NORTH, num)), sw(IntSection(ew, Lane::EAST, num))/*,
			 north(Lane(Lane::NORTH, ne, se, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks)),
			 west(Lane(Lane::WEST, nw, ne, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks)),
			 south(Lane(Lane::SOUTH, sw, nw, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks)),
			 east(Lane(Lane::EAST, se, sw, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks))*/
{	
	// reserve space in memory for the lanes
	lanes.reserve(4);
	
	// interconnect the IntSections
	ne.setNext(nw);
	ne.setBack(se);
	nw.setNext(sw);
	nw.setBack(ne);
	sw.setNext(se);
	sw.setBack(nw);
	se.setNext(ne);
	se.setBack(sw);
	// construct lanes and add to vector
	
	Lane north(Lane::NORTH, ne, se, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks);
	Lane west(Lane::WEST, nw, ne, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks);
	Lane south(Lane::SOUTH, sw, nw, num, prob_new_vehicle_north_south,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks);
	Lane east(Lane::EAST, se, sw, num, prob_new_vehicle_east_west,
						 proportion_of_cars, proportion_of_SUVs, 
						 prob_right_turn_cars, prob_right_turn_SUVs, prob_right_turn_trucks);
	
	lanes.push_back(north);
	lanes.push_back(west);
	lanes.push_back(south);
	lanes.push_back(east);
	ne.setExit(lanes.at(0).link(num, ne, se));
	nw.setExit(lanes.at(1).link(num, nw, ne));
	sw.setExit(lanes.at(2).link(num, sw, nw));
	se.setExit(lanes.at(3).link(num, se, sw));
}

Clock::~Clock() {}

std::vector<Section*> Clock::Tick() 
{
	ns.advanceTick(); // advance traffic lights by one tick
	ew.advanceTick();
	occupied.clear();
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
		temp.clear();
		it++;
	}	
	
	return occupied;
}

#endif
