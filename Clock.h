#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "TrafficLight.h"
#include "Lane.h"
#include <vector>

class Clock
{
	protected:
		TrafficLight ns; // traffic light for north-south
		TrafficLight ew; // traffic light for east-west
		std::vector<Lane> lanes; // list of lanes

	public:
		//Clock();
		Clock(int num, int green_north_south, int yellow_north_south, int green_east_west, int yellow_east_west);
		~Clock();
		void Tick();
};

#endif
