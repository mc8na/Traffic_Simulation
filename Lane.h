// header file contains Lane, Vehicle, Car, SUV, Truck, Section, IntSection classes
#ifndef __LANE_H__
#define __LANE_H__

#include "TrafficLight.h"
#include <vector>
#include <list>
#include <iostream>

class Vehicle;
class Section;
class IntSection;

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
		void proceed(Lane& lane);
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
};

class SUV : public Vehicle
{
	public:
		SUV();
		SUV(Section& sec, Lane::Direction dir);
		void proceed(Lane& lane);
		~SUV();

	protected:
		Section* mid;
};

class Truck : public Vehicle
{
	public:
		Truck();
		Truck(Section& sec, Lane::Direction dir);
		void proceed(Lane& lane);
		~Truck();

	protected:
		Section* frontMid;
		Section* backMid;
};

class Section
{
	public:
		Section();
		Section(Section& sec);
		~Section();
		bool isOpen();
		Section* getNext(Lane::Direction dir);
		void setOpen(bool op);

	protected:
		Section* next;
		bool open;
};

class IntSection : public Section
{
	public:
		IntSection(TrafficLight& tl, Lane::Direction dir);
		void setStraight(Section& sec);
		void setExit(Section& sec);
		Section* getNext(Lane::Direction dir);
		~IntSection();

	protected:
		TrafficLight* traf;
		Section* exit;
		Lane::Direction direction;

};

#endif
