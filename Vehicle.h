#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "Section.h"
#include "Lane.h"

class Vehicle
{
	protected:
		Section front;
		Section back;
		Lane::Direction direction;

	public:
		Vehicle(const Section& sec, Lane::Direction dir);
		~Vehicle();
		void proceed();
		Lane::Direction getDirection();

};

#endif
