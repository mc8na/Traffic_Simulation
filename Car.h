#ifndef __CAR_H__
#define __CAR_H__

#include "Lane.h"
//#include "Vehicle.h"

class Car : public Vehicle
{
	public:
		Car();
		Car(const Section& sec, Lane::Direction dir);
		~Car();

	protected:		
};

#endif
