// header file contains Lane, Vehicle, Car, SUV, Truck, Section, IntSection classes
#ifndef __LANE_H__
#define __LANE_H__

#include "TrafficLight.h"
#include "VehicleBase.h"
#include <vector>
#include <list>
#include <iostream>
#include <random>

class Vehicle;
class Section;
class IntSection;

class Lane
{
	public:
		enum Direction {NORTH, SOUTH, EAST, WEST};
		Lane(const Lane& lane);
		Lane(Direction dir, IntSection& one, IntSection& two, int numSections,
			 double prob_new, double proportion_cars, double proportion_SUVs,
			 double prob_right_cars, double prob_right_SUVs,
			 double prob_right_trucks);
		~Lane();
		void advance();
		void removeVehicle();

	protected:
		std::vector<Section> sections;
		Direction lDirection;
		std::list<Vehicle> vehicles;
		double prob_new_vehicle;
		double proportion_of_cars;
		double proportion_of_SUVs;
		double proportion_of_trucks;
		double prob_right_turn_cars;
		double prob_right_turn_SUVs;
		double prob_right_turn_trucks;
		Vehicle createVehicle(std::uniform_real_distribution<double> rand_double);
		Lane::Direction assignDir(std::uniform_real_distribution<double> rand_double, double prob_right_turn);
};

class Vehicle : public VehicleBase
{
	public:
		//Vehicle();
		Vehicle(const Vehicle& veh);
		Vehicle(Section& sec, Lane::Direction dir, VehicleBase::VehicleType type);
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
		//Car();
		Car(const Car& car);
		Car(Section& sec, Lane::Direction dir);
		~Car();		
};

class SUV : public Vehicle
{
	public:
		//SUV();
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
		//Truck();
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
