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
	indexFirstVehicle = lane.indexFirstVehicle;
	indexLastVehicle = lane.indexLastVehicle;
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
	indexFirstVehicle = 0;
	indexLastVehicle = 0;
	vehicles.reserve(numSections + 2);

	for(int i = 0; i < numSections; i++) // create inbound sections 
	{
		sections.push_back(Section(getDirection(), i));
	}
	sections.push_back(two); // add IntSection
	sections.push_back(one); // add IntSection
	for(int i = numSections + 2; i < 2 * numSections + 2; i++) // create outbound sections
	{
		sections.push_back(Section(getDirection(), i));
	}

	for(int i = 0; i < numSections; i++) // now link sections together
	{
		sections.at(i).setNext(sections.at(i + 1));
	}
	one.setExit(sections.at(numSections + 2));
	for(int i = numSections + 2; i < 2 * numSections + 1; i++)
	{
		sections.at(i).setNext(sections.at(i + 1));
	}
}

Lane::~Lane(){}

std::vector<Section*> Lane::advance()
{
	occupied.clear();
	std::vector<Section*> temp;
	for(int i = indexFirstVehicle; i < indexLastVehicle; i++)
	{
		temp = vehicles.at(i).proceed(*this);
		std::vector<Section*>::iterator it2 = temp.begin();
		while(it2 != temp.end())
		{
			occupied.push_back(*it2);
			it2++;
		}
	}
	//std::list<Vehicle>::iterator it = vehicles.begin();
	//while(it != vehicles.end()) // tell each vehicle in the list to move forward
	//{
	//	temp = (*it).proceed(*this);
	//}
	if(sections.front().isOpen())
	{
		double random = randDouble(0.0, 1.0);
		if(random < prob_new_vehicle)
		{
			std::vector<Vehicle>::iterator it = vehicles.begin() + indexLastVehicle;
			double prob = randDouble(0.0, 1.0);
			if(prob < proportion_of_cars)
			{
				vehicles.insert(it, Car(sections.front(), assignDir(prob, prob_right_turn_cars)));
				//vehicles.push_back(Car(sections.front(), assignDir(prob, prob_right_turn_cars)));
			}
			else if(prob < proportion_of_cars + proportion_of_SUVs)
			{
				vehicles.insert(it, SUV(sections.front(), assignDir(prob, prob_right_turn_SUVs)));
			}
			else
			{
				vehicles.insert(it, Truck(sections.front(), assignDir(prob, prob_right_turn_trucks)));
			}
			indexLastVehicle = (indexLastVehicle + 1) % vehicles.capacity();
			occupied.push_back(&(sections.front()));
		}
	}
	return occupied;
}

void Lane::removeVehicle() // remove vehicle when it exits the lane
{
	//vehicles.pop_front();
	indexFirstVehicle = (indexFirstVehicle + 1) % vehicles.capacity();
}

Lane::Direction Lane::assignDir(double prob, double prob_right_turn)
{
	prob = randDouble(0.0, 1.0);
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

double Lane::randDouble(double low, double high) 
{
	return ( ( double )rand() * ( high - low ) ) / ( double )RAND_MAX + low;
}

#endif
