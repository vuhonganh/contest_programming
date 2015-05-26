CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall
CXXFLAGS = -O2 -std=c++11 -Wall

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = networkX

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input
out: $(exe)
	./$< < input > output

.PHONY: clean

clean:
	rm -rf $(exe) output
