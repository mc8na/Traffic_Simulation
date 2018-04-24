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
		Lane(const Lane& lane);
		Lane(Direction dir, IntSection& one, IntSection& two, int numSections);
		~Lane();
		void advance();
		void removeVehicle();

	protected:
		std::vector<Section> sections;
		Direction lDirection;
		std::list<Vehicle> inbound;
		std::list<Vehicle> outbound;
};

class Vehicle
{
	public:
		Vehicle();
		Vehicle(const Vehicle& veh);
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
		Car(const Car& car);
		Car(Section& sec, Lane::Direction dir);
		~Car();		
};

class SUV : public Vehicle
{
	public:
		SUV();
		SUV(const SUV& suv);
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
		Truck(const Truck& truck);
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
		Section(const Section& sec);
		~Section();
		bool isOpen();
		Section* getNext(Lane::Direction dir);
		void setOpen(bool op);
		void setNext(Section& sec);

	protected:
		Section* next;
		bool open;
};

class IntSection : public Section
{
	public:
		IntSection(const IntSection& sec);
		IntSection(TrafficLight& tl, Lane::Direction dir);
		void setExit(Section& sec);
		Section* getNext(Lane::Direction dir);
		bool isOpen();
		~IntSection();

	protected:
		TrafficLight* traf;
		Section* out;
		Lane::Direction direction;

};

#endif
