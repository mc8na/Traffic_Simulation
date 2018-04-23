#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "TrafficLight.h"
#include "Section.h"
#include "Lane.h"
#include <vector>

class Clock
{
	protected:
		TrafficLight* ns;
		TrafficLight* ew;
		std::vector<Lane*> lanes;

	public:
		//Clock();
		Clock(int num, int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west);
		~Clock();
};

#endif
