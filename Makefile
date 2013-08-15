CFLAGS=-Wall -g -std=c++11
LDFLAGS=-lpthread



all:driver queue.o


driver:driver_dine.cpp queue.o philosopher.tcc philosopher.hpp
	g++ ${CFLAGS} -o driver driver_dine.cpp queue.o ${LDFLAGS} 

queue.o:queue.hpp queue.cpp
	g++ ${CFLAGS} -c queue.cpp


clean:
	rm -rf driver queue.o
