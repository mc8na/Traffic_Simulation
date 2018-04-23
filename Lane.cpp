#ifndef __LANE_CPP__
#define __LANE_CPP__

#include "Lane.h"
#include <vector>
#include <list>

Lane::Lane(Direction dir, IntSection& one, IntSection& two, int numSections)
{
	lDirection = dir;
	Section *sec = new Section();
	sections.push_back(sec);
	for(int i = 1; i < numSections; i++)
	{
		Section *sect = new Section(*(sections.at(i-1)));
		sections.push_back(sect);
	}
	one.setExit(*(sections.at(numSections-1)));
	sections.push_back(&one);
	sections.push_back(&two);
	for(int i = numSections + 2; i < 2 * numSections + 2; i++)
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
