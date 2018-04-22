#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "Lane.h"
//#include "Vehicle.h"

class Truck : public Vehicle
{
	public:
		Truck();
		Truck(const Section& sec, Lane::Direction dir);
		~Truck();

	protected:
		Section frontMid;
		Section backMid;
};

#endif
