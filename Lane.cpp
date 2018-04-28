#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <vector>
#include <list>

Lane::Lane(const Lane& lane)
{
	sections = lane.sections;
	lDirection = lane.lDirection;
	vehicles = lane.vehicles;
	prob_new_vehicle = lane.prob_new_vehicle;
	proportion_of_cars = lane.proportion_of_cars;
	proportion_of_SUVs = lane.proportion_of_SUVs;
	prob_right_turn_cars = lane.prob_right_turn_cars;
	prob_right_turn_SUVs = lane.prob_right_turn_SUVs;
	prob_right_turn_trucks = lane.prob_right_turn_trucks;
}

Lane::Lane(Direction dir, IntSection& one, IntSection& two, int numSections,
		   double prob_new, double proportion_cars, double proportion_SUVs,
		   double prob_right_cars, double prob_right_SUVs,
		   double prob_right_trucks)
{
	lDirection = dir; // assign the Lane a direction
	prob_new_vehicle = prob_new;
	proportion_of_cars = proportion_cars;
	proportion_of_SUVs = proportion_SUVs;
	prob_right_turn_cars = prob_right_cars;
	prob_right_turn_SUVs = prob_right_SUVs;
	prob_right_turn_trucks = prob_right_trucks;
	sections.push_back(Section(getDirection(), 0));
	for(int i = 1; i < numSections; i++) // create inbound sections and link to one another
	{
		sections.push_back(Section(getDirection(), i));
		sections.at(i-1).setNext(sections.at(i));
	}
	sections.push_back(two); // add IntSection
	sections.at(numSections-1).setNext(two); // link Section to IntSection
	sections.push_back(one); // add IntSection
	sections.push_back(Section(getDirection(), numSections + 2));
	one.setExit(sections.at(numSections + 2)); // link IntSection to outbound Sections
	for(int i = numSections + 3; i < 2 * numSections + 2; i++) // create and link outbound sections
	{
		sections.push_back(Section(getDirection(), i));
		sections.at(i-1).setNext(sections.at(i));
	}
}

Lane::~Lane(){}

std::vector<Section*> Lane::advance()
{
	std::vector<Section*> occupied;
	std::vector<Section*> temp;
	std::list<Vehicle>::iterator it = vehicles.begin();
	while(it != vehicles.end()) // tell each vehicle in the list to move forward
	{
		temp = (*it).proceed(*this);
		std::vector<Section*>::iterator it2 = temp.begin();
		while(it2 != temp.end())
		{
			occupied.push_back(*it2);
			it2++;
		}
		it++;
	}
	if(sections.front().isOpen())
	{
		double random = randDouble(0.0, 1.0);
		if(random < prob_new_vehicle)
		{
			vehicles.push_back(createVehicle(random));
		}
	}
	return occupied;
}

void Lane::removeVehicle() // remove vehicle when it exits the lane
{
	vehicles.pop_front();
}

Vehicle Lane::createVehicle(double prob)
{
	prob = randDouble(0.0, 1.0);
	if(prob < proportion_of_cars)
	{
		
		Vehicle veh = Car(sections.front(), assignDir(prob, prob_right_turn_cars));
		return veh;

	}
	else if(prob < proportion_of_cars + proportion_of_SUVs)
	{
		Vehicle veh = SUV(sections.front(), assignDir(prob, prob_right_turn_SUVs));
		return veh;
	}
	else
	{
		Vehicle veh = Truck(sections.front(), assignDir(prob, prob_right_turn_trucks));
		return veh;
	}
		
}

Lane::Direction Lane::assignDir(double prob, double prob_right_turn)
{
	prob = randDouble(0.0, 1.0);
	std::cout << randDouble(0.0, 1.0) << std::endl;
	switch(prob < prob_right_turn)
	{
		case true:
			switch(lDirection)
			{
				case Lane::NORTH:
					return Lane::EAST;
				case Lane::SOUTH:
					return Lane::WEST;
				case Lane::EAST:
					return Lane::SOUTH;
				case Lane::WEST:
					return Lane::NORTH;
			}
		case false:
			return lDirection;
	}
}

Lane::Direction Lane::getDirection()
{
	return lDirection;
}

double Lane::randDouble(double low, double high) {
	return ( ( double )rand() * ( high - low ) ) / ( double )RAND_MAX + low;
}

#endif
