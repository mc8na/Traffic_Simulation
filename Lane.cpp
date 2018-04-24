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
		sections.at(i-1).setNext(sections.at(i));
	}
	sections.push_back(two);
	sections.at(numSections-1).setNext(two);
	sections.push_back(one);
	//one.setExit(sections.at(numSections-1)); // IntSection exit points to outbound Sections
	//sections.push_back(one);
	//sections.push_back(two);
	sections.push_back(Section());
	one.setExit(sections.at(numSections + 2));
	for(int i = numSections + 3; i < 2 * numSections + 2; i++) // fill in inbound Sections
	{
		//Section sect(sections.at(i-1));// = new Section(*(sections.at(i-1)));
		sections.push_back(Section());
		sections.at(i-1).setNext(sections.at(i));
	}
	//sections.at(numSections-1).setNext(sections.at(numSections));
	//one.setExit(sections.at(numSections+2))
}

Lane::~Lane(){}

void Lane::advanceOutbound()
{
	std::list<Vehicle>::iterator it = outbound.begin();
	while(it != outbound.end())
	{
		(*it).proceed(*this);
		it++;
	}
}

void Lane::advanceInbound()
{
	std::list<Vehicle>::iterator it = inbound.begin();
	while(it != inbound.end())
	{
		(*it).proceed(*this);
		it++;
	}
	if(sections.front().isOpen())
	{
		Vehicle veh(sections.back(), lDirection);
		inbound.push_back(veh);
	}
}


void Lane::removeVehicle() 
{
	outbound.pop_front();
}

#endif
