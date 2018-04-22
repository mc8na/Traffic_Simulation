#ifndef __CAR_CPP__
#define __CAR_CPP__

//#include "Intersection.h"
#include "Lane.h"

Car::Car() : Vehicle() {}

Car::Car(const Section& sec, Lane::Direction dir) : Vehicle(sec, dir) {}

Car::~Car() {}

#endif
