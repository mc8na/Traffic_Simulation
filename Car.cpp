#ifndef __CAR_CPP__
#define __CAR_CPP__

#include "Lane.h"

Car::Car() : Vehicle() {}

Car::Car(Section& sec, Lane::Direction dir) : Vehicle(sec, dir) {}

Car::~Car() {}

#endif
