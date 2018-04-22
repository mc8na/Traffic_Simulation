#ifndef __LANE_CPP__
#define __LANE_CPP__

//#include "Intersection.h"
#include "Lane.h"
#include <vector>
#include <list>

Lane::Lane(Direction dir, IntSection one, IntSection two, int numSections)
{
	lDirection = dir;
	 
}

Lane::~Lane(){}

void Lane::advance()
{

}

#endif
