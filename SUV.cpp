#ifndef __SUV_CPP__
#define __SUV_CPP__

#include "Lane.h"

SUV::SUV() : Vehicle() {}

SUV::SUV(const Section& sec, Lane::Direction dir) : Vehicle(sec, dir) {}

SUV::~SUV() {}

#endif
