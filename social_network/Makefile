simulator_Q1: driver.o FriendNet.o Queue.o
	g++ -g driver.o FriendNet.o Queue.o -o simulator_Q1
driver.o: driver.cpp
	g++ -g -c driver.cpp
FriendNet.o: FriendNet.cpp FriendNet.h
	g++ -g -c FriendNet.cpp FriendNet.h
Queue.o: Queue.cpp Queue.h QueueException.h
	g++ -g -c Queue.cpp Queue.h QueueException.h
clean:
	rm *.o simulator_Q1 *.gch
