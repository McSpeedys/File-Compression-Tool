OBJS = main.o compressor.o 
COMP = g++
ARGS = -g -Wall

exe: main.o compressor.o

main.o: compressor.cpp  

compressor.o: compressor.cpp compressor.h

clean:
	./rm *.o *exe

