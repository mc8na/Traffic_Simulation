#ifndef __CAR_CPP__
#define __CAR_CPP__

#include "Lane.h"

//Car::Car() : Vehicle() {}

Car::Car(const Car& car) : Vehicle(car) {}

Car::Car(Section& sec, Lane::Direction dir) : Vehicle(sec, dir, VehicleBase::CAR) {}

std::vector<Section*> Car::proceed(Lane& lane)
{
	return Vehicle::proceed(lane);
}

Car::~Car() {}

#endif
