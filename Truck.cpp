#ifndef __TRUCK_CPP__
#define __TRUCK_CPP__

//#include "Intersection.h"
#include "Lane.h"

Truck::Truck() : Vehicle() {}

Truck::Truck(const Section& sec, Lane::Direction dir) : Vehicle(sec, dir) {}

Truck::~Truck() {}

#endif
