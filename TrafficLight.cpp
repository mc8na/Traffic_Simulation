#ifndef __TRAFFICLIGHT_CPP__
#define __TRAFFICLIGHT_CPP__

#include "TrafficLight.h"

TrafficLight::TrafficLight() {}

TrafficLight::TrafficLight(TrafficLight::Color col, int green, int yellow)
{
	time = 0;
	color = col;
	lengthGreen = green;
	lengthYellow = yellow;
	lengthRed = green + yellow;
}

TrafficLight::~TrafficLight(){}

void TrafficLight::advanceTick()
{
	time++; // advance time 
	switch(getColor()) // see what color the traffic light is now
	{
		case TrafficLight::RED:
			if(time >= lengthRed) // if it is time to change color
			{
				time = 0;
				color = TrafficLight::GREEN;
			}
		case TrafficLight::GREEN:
			if(time >= lengthGreen) // if it is time to change color
			{
				time = 0;
				color = TrafficLight::YELLOW;
			}
		case TrafficLight::YELLOW:
			if(time >= lengthYellow) // if it is time to change color
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
