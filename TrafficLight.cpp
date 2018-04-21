#ifndef __TRAFFICLIGHT_CPP__
#define __TRAFFICLIGHT_CPP__

#include "TrafficLight.h"

TrafficLight::TrafficLight() {}

TrafficLight::TrafficLight(TrafficLight::Color col, int red, int green)
{
	color = col;
	lengthRed = red;
	lengthGreen = green;
	lengthYellow = red - green;
}

TrafficLight::~TrafficLight(){}

void TrafficLight::advanceTick()
{

}

TrafficLight::Color TrafficLight::getColor()
{
	return color;
}

#endif
