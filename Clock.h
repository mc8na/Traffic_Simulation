#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "TrafficLight.h"
#include "Lane.h"

class Clock
{
	protected:
		TrafficLight ns;
		TrafficLight ew;
		

	public:
		Clock();
		Clock(int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west);
		~Clock();
};

#endif
