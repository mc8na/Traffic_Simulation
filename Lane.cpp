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
}

Lane::Lane(Direction dir, IntSection& one, IntSection& two, int numSections)
{
	lDirection = dir; // assign the Lane a direction
	sections.push_back(Section());
	for(int i = 1; i < numSections; i++) // create inbound sections and link to one another
	{
		sections.push_back(Section());
		sections.at(i-1).setNext(sections.at(i));
	}
	sections.push_back(two); // add IntSection
	sections.at(numSections-1).setNext(two); // link Section to IntSection
	sections.push_back(one); // add IntSection
	sections.push_back(Section());
	one.setExit(sections.at(numSections + 2)); // link IntSection to outbound Sections
	for(int i = numSections + 3; i < 2 * numSections + 2; i++) // create and link outbound sections
	{
		sections.push_back(Section());
		sections.at(i-1).setNext(sections.at(i));
	}
}

Lane::~Lane(){}

void Lane::advance()
{
	std::list<Vehicle>::iterator it = vehicles.begin();
	while(it != vehicles.end()) // tell each vehicle in the list to move forward
	{
		(*it).proceed(*this);
		it++;
	}
}

void Lane::removeVehicle() // remove vehicle when it exits the lane
{
	vehicles.pop_front();
}

#endif
