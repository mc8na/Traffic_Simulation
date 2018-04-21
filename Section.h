#ifndef __SECTION_H__
#define __SECTION_H__

class Section
{
	public:
		Section(const Section& sec);
		~Section();
		bool isOpen();
		Section& getNext();

	protected:
		Section* next;
		bool open;

	
		

};

#endif
