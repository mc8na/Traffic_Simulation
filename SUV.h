#ifndef __SUV_H__
#define __SUV_H__

#include "Vehicle.h"

class SUV : public Vehicle
{
	public:
		SUV();
		~SUV();

	protected:
		Section mid;
};

#endif
