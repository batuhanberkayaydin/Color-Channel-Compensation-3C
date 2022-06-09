CC = g++
#CFLAGS = -g -Wall

CFLAGS +=-std=c++14 -I ./
SRCS = *.cpp
PROG = main

OPENCV = `pkg-config opencv4 --cflags --libs`
    

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(OPENCV)

clean:
	rm -f main main.o
	rm -rf main