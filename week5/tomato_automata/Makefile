CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS =    -std=c++11 -Wall -g 
CXXFLAGS =  -std=c++11 -Wall -g 

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = automata

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input

out: $(exe)
	./$< < input > output
.PHONY: clean

clean:
	rm -rf $(exe) output
