#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <vector>
#include <list>

Lane::Lane(Direction dir, IntSection& one, IntSection& two, int numSections)
{
	lDirection = dir;
	Section *sec = new Section(); // end of outbound lane
	sections.push_back(sec);
	for(int i = 1; i < numSections; i++) // link Sections to each other and add to vector
	{
		Section *sect = new Section(*(sections.at(i-1)));
		sections.push_back(sect);
	}
	one.setExit(*(sections.at(numSections-1))); // IntSection exit points to outbound Sections
	sections.push_back(&one);
	sections.push_back(&two);
	for(int i = numSections + 2; i < 2 * numSections + 2; i++) // fill in inbound Sections
	{
		Section *sect = new Section(*(sections.at(i-1)));
		sections.push_back(sect);
	}
}

Lane::~Lane(){}

void Lane::advance()
{

}

#endif
