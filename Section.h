#ifndef __SECTION_H__
#define __SECTION_H__

#include "TrafficLight.h"

class Section
{
	public:
		Section();
		Section(Section& sec);
		~Section();
		bool isOpen();
		Section* getNext();
		void setOpen(bool op);

	protected:
		Section* next;
		bool open;
};

class IntSection : public Section
{
	public:
		IntSection(TrafficLight& tl);
		void setStraight(Section& sec);
		void setExit(Section& sec);
		~IntSection();

	protected:
		TrafficLight traf;
		Section* exit;

};

#endif
