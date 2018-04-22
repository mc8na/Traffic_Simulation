EXECS = test
OBJS = Vehicle.o Lane.o Clock.o Car.o SUV.o Truck.o Section.o IntSection.o TrafficLight.o

CC = g++
CCFLAGS = -Wall -Wno-deprecated -Werror=return-type -g

all: $(EXECS)

test: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
