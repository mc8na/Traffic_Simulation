#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "Vehicle.h"

class Truck : public Vehicle
{
	public:
		Truck();
		~Truck();

	protected:
		Section frontMid;
		Section backMid;
};

#endif
