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
		std::vector<Section*> advance();
		void removeVehicle();
		Lane::Direction getDirection();
		double randDouble(double low, double high);

	protected:
		std::vector<Section> sections;
		Direction lDirection;
		std::vector<Vehicle> vehicles;
		int indexFirstVehicle;
		int indexLastVehicle;
		std::vector<Section*> occupied;
		double prob_new_vehicle;
		double proportion_of_cars;
		double proportion_of_SUVs;
		double proportion_of_trucks;
		double prob_right_turn_cars;
		double prob_right_turn_SUVs;
		double prob_right_turn_trucks;
		Lane::Direction assignDir(double prob, double prob_right_turn);
};

class Vehicle : public VehicleBase
{
	public:
		//Vehicle();
		Vehicle(const Vehicle& veh);
		Vehicle(Section& sec, Lane::Direction dir, VehicleBase::VehicleType type);
		~Vehicle();
		std::vector<Section*> proceed(Lane& lane);
		Lane::Direction getDirection();
		void operator=(const Vehicle& veh);

	protected:
		Lane::Direction vDirection;
		std::vector<Section*> location; 
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
		std::vector<Section*> proceed(Lane& lane);
		~SUV();

	protected:
		//Section* mid;
};

class Truck : public Vehicle
{
	public:
		//Truck();
		Truck(const Truck& truck);
		Truck(Section& sec, Lane::Direction dir);
		std::vector<Section*> proceed(Lane& lane);
		~Truck();

	protected:
		//Section* frontMid;
		//Section* backMid;
};

class Section
{
	public:
		Section(Lane::Direction l, int i);
		Section(const Section& sec);
		~Section();
		bool isOpen();
		Section* getNext(Lane::Direction dir);
		void occupy(Vehicle& veh);
		void leave();
		void setNext(Section& sec);
		int getIndex();
		Vehicle* getVehicle();
		Lane::Direction getLane();

	protected:
		Section* next;
		bool open;
		Lane::Direction lane;
		Vehicle* vehicle;
		int index;
};

class IntSection : public Section
{
	public:
		IntSection(const IntSection& sec);
		IntSection(TrafficLight& tl, Lane::Direction dir, int i);
		void setExit(Section& sec);
		Section* getNext(Lane::Direction dir);
		bool isOpen();
		~IntSection();

	protected:
		TrafficLight* traf;
		Section* out;

};

#endif
