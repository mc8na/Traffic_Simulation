#ifndef __LANE_H__
#define __LANE_H__

#include "Section.h"
#include <vector>
#include <list>
#include <iostream>

class Section;
class Vehicle;

class Lane
{
	public:
		enum Direction {NORTH, SOUTH, EAST, WEST};
		Lane(Direction dir, IntSection& one, IntSection& two, int numSections);
		~Lane();
		void advance();

	protected:
		std::vector<Section*> sections;
		Direction lDirection;
		std::list<Vehicle> inbound;
		std::list<Vehicle> outbound;
};

class Vehicle
{
	public:
		Vehicle();
		Vehicle(Section& sec, Lane::Direction dir);
		~Vehicle();
		void proceed();
		Lane::Direction getDirection();

	protected:
		Section* front;
		Section* back;
		Lane::Direction vDirection;
};

class Car : public Vehicle
{
	public:
		Car();
		Car(Section& sec, Lane::Direction dir);
		~Car();

	protected:		
};

class SUV : public Vehicle
{
	public:
		SUV();
		SUV(Section& sec, Lane::Direction dir);
		void proceed();
		~SUV();

	protected:
		Section* mid;
};

class Truck : public Vehicle
{
	public:
		Truck();
		Truck(Section& sec, Lane::Direction dir);
		void proceed();
		~Truck();

	protected:
		Section* frontMid;
		Section* backMid;
};

#endif
