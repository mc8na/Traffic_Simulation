#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <vector>
#include <list>

Lane::Lane(const Lane& lane)
{
	sections = lane.sections;
	lDirection = lane.lDirection;
	inbound = lane.inbound;
	outbound = lane.outbound;
}

Lane::Lane(Direction dir, IntSection& one, IntSection& two, int numSections)
{
	lDirection = dir;
	//Section sec; // end of outbound lane
	sections.push_back(Section());
	for(int i = 1; i < numSections; i++) // link Sections to each other and add to vector
	{
		//Section sect(sections.at(i-1));// = new Section(*(sections.at(i-1)));
		sections.push_back(Section());
		sections.at(i).setNext(sections.at(i-1));
	}
	one.setExit(sections.at(numSections-1)); // IntSection exit points to outbound Sections
	sections.push_back(one);
	sections.push_back(two);
	for(int i = numSections + 2; i < 2 * numSections + 2; i++) // fill in inbound Sections
	{
		//Section sect(sections.at(i-1));// = new Section(*(sections.at(i-1)));
		sections.push_back(Section());
		sections.at(i).setNext(sections.at(i-1));
	}
}

Lane::~Lane(){}

void Lane::advance()
{

}

void Lane::removeVehicle(Vehicle& veh) 
{

}

#endif
