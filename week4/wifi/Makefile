CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall -g
CXXFLAGS = -O2 -std=c++11 -Wall -g

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = wifi

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input

out: $(exe)
	./$< < input > output
debug: $(exe)
	gdb ./$< input

.PHONY: clean

clean:
	rm -rf $(exe) output
