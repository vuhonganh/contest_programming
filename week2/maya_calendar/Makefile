CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall
CXXFLAGS = -O2 -std=c++11 -Wall

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = maya_calendar

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input.txt

out: $(exe)
	./$< < input.txt > output.txt
.PHONY: clean

clean:
	rm -rf $(exe)
