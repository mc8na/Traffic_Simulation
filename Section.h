#ifndef __SECTION_H__
#define __SECTION_H__

#include "TrafficLight.h"
#include "Lane.h"

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
