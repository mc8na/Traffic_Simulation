#ifndef __TRAFFICLIGHT_H__
#define __TRAFFICLIGHT_H__

class TrafficLight
{
	public:
		enum Color {RED, YELLOW, GREEN};
		TrafficLight();
		TrafficLight(Color col, int green, int yellow);
		~TrafficLight();
		void advanceTick();
		Color getColor();

	protected:
		Color color;
		int lengthRed;
		int lengthYellow;
		int lengthGreen;
		int time;	
};

#endif
