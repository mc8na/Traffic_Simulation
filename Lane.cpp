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
	sections.push_back(Section(this, 0));
	for(int i = 1; i < numSections; i++) // create inbound sections and link to one another
	{
		sections.push_back(Section(this, i));
		sections.at(i-1).setNext(sections.at(i));
	}
	sections.push_back(two); // add IntSection
	sections.at(numSections-1).setNext(two); // link Section to IntSection
	sections.push_back(one); // add IntSection
	sections.push_back(Section(this, numSections + 2));
	one.setExit(sections.at(numSections + 2)); // link IntSection to outbound Sections
	for(int i = numSections + 3; i < 2 * numSections + 2; i++) // create and link outbound sections
	{
		sections.push_back(Section(this, i));
		sections.at(i-1).setNext(sections.at(i));
	}
}

Lane::~Lane(){}

void Lane::advance()
{
	std::list<Vehicle>::iterator it = vehicles.begin();
	while(it != vehicles.end()) // tell each vehicle in the list to move forward
	{
		std::vector<Section*> location = (*it).proceed(*this);
		it++;
	}
	if(sections.front().isOpen())
	{
		std::mt19937 rng(8675308);
		std::uniform_real_distribution<double> rand_double(0.0, 1.0);
		if(rand_double(rng) < prob_new_vehicle)
		{
			vehicles.push_back(createVehicle(rand_double));
		}
	}
}

void Lane::removeVehicle() // remove vehicle when it exits the lane
{
	vehicles.pop_front();
}

Vehicle Lane::createVehicle(std::uniform_real_distribution<double> rand_double)
{
	std::mt19937 rng(8675308);
	double prob = rand_double(rng);
	if(prob < proportion_of_cars)
	{
		
		Vehicle veh = Car(sections.front(), assignDir(rand_double, prob_right_turn_cars));
		return veh;

	}
	else if(prob < proportion_of_cars + proportion_of_SUVs)
	{
		Vehicle veh = SUV(sections.front(), assignDir(rand_double, prob_right_turn_SUVs));
		return veh;
	}
	else
	{
		Vehicle veh = Truck(sections.front(), assignDir(rand_double, prob_right_turn_trucks));
		return veh;
	}
		
}

Lane::Direction Lane::assignDir(std::uniform_real_distribution<double> rand_double, double prob_right_turn)
{
	std::mt19937 rng(8675308);
	double prob = rand_double(rng);
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

#endif
