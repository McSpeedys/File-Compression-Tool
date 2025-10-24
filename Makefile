OBJS = main.o compressor.o 
CC = g++
DEBUG = -g
CFALGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


compress.exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o compress.exe

main.o: compressor.cpp compressor.h
	$(CC) $(CFLAGS) main.cpp 

compressor.o: compressor.cpp compressor.h
	$(CC) $(CFALGS) compressor.cpp 

clean:
	\rm *.o *compress.exe

