#ifndef __LANE_H__
#define __LANE_H__

//#include "IntSection.h"
//#include "Vehicle.h"
#include "Section.h"
#include <vector>
#include <list>

class Section;
class Vehicle;

class Lane
{
	public:
		enum Direction {NORTH, SOUTH, EAST, WEST};
		Lane(Direction dir, IntSection one, IntSection two, int numSections);
		~Lane();
		void advance();

	protected:
		std::vector<Section> sections;
		Direction lDirection;
		std::list<Vehicle> vehicles;
};

class Vehicle
{
	public:
		Vehicle();
		Vehicle(const Section& sec, Lane::Direction dir);
		~Vehicle();
		void proceed();
		Lane::Direction getDirection();

	protected:
		Section front;
		Section back;
		Lane::Direction vDirection;
};

class Car : public Vehicle
{
	public:
		Car();
		~Car();

	protected:		
};

class SUV : public Vehicle
{
	public:
		SUV();
		~SUV();

	protected:
		Section mid;
};

class Truck : public Vehicle
{
	public:
		Truck();
		~Truck();

	protected:
		Section frontMid;
		Section backMid;
};

#endif
