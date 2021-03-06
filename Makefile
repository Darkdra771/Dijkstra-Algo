runner.out: RoadRunner.o tripper.o
	g++ -Wall -g  -ansi  -o runner.out RoadRunner.o tripper.o 

RoadRunner.o: RoadRunner.cpp RoadRunner.h CPUTimer.h tripper.h 
	g++ -Wall -g  -ansi  -c RoadRunner.cpp

tripper.o: tripper.cpp tripper.h RoadRunner.h QueueAr.h QuadraticProbing.h BinaryHeap.h StackAr.h 
	g++ -Wall -g  -ansi  -c tripper.cpp

clean:
	rm -f runner.out RoadRunner.o tripper.o 
