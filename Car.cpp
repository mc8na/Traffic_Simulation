#ifndef __CAR_CPP__
#define __CAR_CPP__

#include "Lane.h"

Car::Car() : Vehicle() {}

Car::Car(const Car& car) : Vehicle(car) {}

Car::Car(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) {}

Car::~Car() {}

#endif
