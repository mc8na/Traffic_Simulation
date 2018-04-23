#ifndef __TRAFFICLIGHT_CPP__
#define __TRAFFICLIGHT_CPP__

#include "TrafficLight.h"

TrafficLight::TrafficLight() {}

TrafficLight::TrafficLight(TrafficLight::Color col, int red, int green)
{
	time = 0;
	color = col;
	lengthRed = red;
	lengthGreen = green;
	lengthYellow = red - green;
}

TrafficLight::~TrafficLight(){}

void TrafficLight::advanceTick()
{
	time++;
	switch(getColor())
	{
		case TrafficLight::RED:
			if(time >= lengthRed)
			{
				time = 0;
				color = TrafficLight::GREEN;
			}
		case TrafficLight::GREEN:
			if(time >= lengthGreen)
			{
				time = 0;
				color = TrafficLight::YELLOW;
			}
		case TrafficLight::YELLOW:
			if(time >= lengthYellow)
			{
				time = 0;
				color = TrafficLight::RED;
			}
	}
}

TrafficLight::Color TrafficLight::getColor()
{
	return color;
}

#endif
