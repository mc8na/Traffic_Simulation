#ifndef __SUV_H__
#define __SUV_H__

#include "Lane.h"
//#include "Vehicle.h"

class SUV : public Vehicle
{
	public:
		SUV();
		SUV(const Section& sec, Lane::Direction dir);
		~SUV();

	protected:
		Section mid;
};

#endif
