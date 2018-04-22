#ifndef __SECTION_H__
#define __SECTION_H__

#include "TrafficLight.h"

class Section
{
	public:
		Section();
		Section(const Section& sec);
		~Section();
		bool isOpen();
		Section& getNext();

	protected:
		Section* next;
		bool open;
};

class IntSection : public Section
{
	public:
		IntSection(Section straight, Section turn, TrafficLight tl);
		~IntSection();

	protected:
		TrafficLight traf;
		Section exit;

};

#endif
